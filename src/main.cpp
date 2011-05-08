/*
 * Copyright (c) 2008,2009,2011 Jérémie DECOCK <jd.jdhp@gmail.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <math.h>
#include <sys/time.h>
#include <getopt.h>

#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

#include <btBulletDynamicsCommon.h>
#include <iostream>
#include <string>

#include "agents/Controller.h"
#include "simulator/views/Views.h"
#include "simulator/environments/Environments.h"
#include "simulator/robots/Robots.h"
#include "simulator/World.h"

/* Nombre de secondes écoulées dans la simulation (ie pour le moteur)
   à chaque appel de stepSimulation */
const double TICK_DURATION = 1. / 70.;

/* Nombre de us séparant deux appels à la méthode stepSimulation */
const int TICK_INTERVAL = 10000;

static void usage();

static void print_version();

int main(int argc, char ** argv) {
    
    typedef enum {bot1, bot2, robudog} robot_id_t;

    // GETOPT ///////////////////////////////////

    bool viewFlag = true;
    robot_id_t robot_id = robudog;

    int c;
    while(1) {
        static struct option long_options[] =
        {
            {"no-gui",  no_argument,       0, 'n'},
            {"robot",   required_argument, 0, 'r'},
            {"help",    no_argument,       0, 'h'},
            {"version", no_argument,       0, 'v'},
            {0, 0, 0, 0}
        };

        /* getopt_long stores the option index here */
        int option_index = 0;

        c = getopt_long(argc, argv, "nr:hv", long_options, &option_index);

        /* detect the end of the options */
        if(c == -1)
            break;

        switch (c) {
            case 'n':
                viewFlag = false;
                break;
            case 'r':
                if(0 == strcmp(optarg, "bot1")) {
                    robot_id = bot1;
                } else if(0 == strcmp(optarg, "bot2")) {
                    robot_id = bot2;
                } else {
                    robot_id = robudog;
                }
                break;
            case 'h':
                usage();
                exit(EXIT_SUCCESS);
                break;
            case 'v':
                print_version();
                exit(EXIT_SUCCESS);
                break;
            case '?':
                usage();
                exit(EXIT_FAILURE);
        }
    }

    // INIT SIMULATION //////////////////////////
    World * world = World::createWorld();
    Flat * environment = new Flat();

    void (* pmove) (struct timeval, Robot *);

    Robot * bot;

    switch(robot_id) {
        case bot1 :
            bot = new Bot1();
            pmove = moveBot1;
            break;
        case bot2 :
            bot = new Bot2();
            pmove = moveBot2;
            break;
        case robudog :
            bot = new Robudog();
            pmove = moveRobudog;
            break;
        default :
            std::cout << "Error: unknown robot id" << std::endl;
            exit(EXIT_FAILURE);
    }

    world->setEnvironment(environment);
    world->setRobot(bot);

    OSGView * view = NULL;

    if(viewFlag) {
        view = new OSGView();
        view->setWorld(world);
        view->run();
    }

    // INIT TIMERS
    struct timeval timev_init;  // Initial absolute time (static)
    struct timeval timev_prev;  // Previous tick absolute time
    struct timeval timev_cur;   // Current tick absolute time
    struct timeval timev_rel;   // Current relative time (curent time - initial time)
    struct timeval timev_diff;  // Tick duration (curent tick time - previous tick time)
    
    timerclear(&timev_init);
    gettimeofday(&timev_init, NULL);

    // FIRST TICK
    timev_cur = timev_init;
    world->stepSimulation(TICK_DURATION, 0); // On fait *une* step de 1/100s
    timev_prev = timev_cur;

    // TICKS LOOP
    while(true) {
        gettimeofday(&timev_cur, NULL);
        timersub(&timev_cur, &timev_prev, &timev_diff);

        // On fait un step de 1/100s toutes les 10000us
        if(timev_diff.tv_usec > TICK_INTERVAL || timev_diff.tv_sec > 0) {

            // Calculate relative time //////////////////////////
            timersub(&timev_cur, &timev_init, &timev_rel);

            // Debug info ///////////////////////////////////////
            //std::cout << bot->getTrunk() << std::endl;

            // Move robot ///////////////////////////////////////
            (*pmove) (timev_rel, bot);

            // Step simulation ///////////////////////////////////
            world->stepSimulation(TICK_DURATION, 0); // On fait *une* step de 1/100s

            timev_prev = timev_cur;

        }
    }

    delete environment;
    delete bot;
    //delete world;
    if(view != NULL)
        delete view;
    
    exit(EXIT_SUCCESS);
}

static void usage() {
    std::string msg =
        "A robots simulator mainly used to test some evolutionary algorithms.\n\n"
        "Usage: botsim [OPTION]...\n\n"
        "Options:\n"
        "   -n, --no-gui      disable the graphic user interface\n"
        "   -r, --robot=NAME  set the robot to use (bot1, bot2 or robudog)\n"
        "   -h, --help        display this help and exit\n"
        "   -v, --version     output version information and exit\n";

    std::cout << msg;
}

static void print_version() {
    std::string msg =
        "Botsim 0.1\n\n"
        "Copyright (c) 2008,2009,2011 Jeremie Decock <jd.jdhp@gmail.com>.\n"
        "This is free software; see the source for copying conditions.\n"
        "There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n";

    std::cout << msg;
}

