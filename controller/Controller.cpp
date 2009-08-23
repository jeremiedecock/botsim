/*
 * Copyright (c) 2008, 2009 Jérémie DECOCK <webmaster@jdhp.org>
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
#include <iostream>
#include <stdio.h>

#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef VIEWS_HEADERS
    #define   VIEWS_HEADERS
    #include "../simulator/views/Views.h"
#endif

#ifndef ENVIRONMENTS_HEADERS
    #define  ENVIRONMENTS_HEADERS
    #include "../simulator/environments/Environments.h"
#endif

#ifndef ROBOTS_HEADERS
    #define ROBOTS_HEADERS
    #include "../simulator/robots/Robots.h"
#endif

#ifndef BULLET_HEADERS
    #define BULLET_HEADERS
    #include <btBulletDynamicsCommon.h>
#endif

#ifndef WORLD_HEADER
    #define WORLD_HEADER
    #include "../simulator/World.h"
#endif

#ifndef STRING_HEADER
    #define STRING_HEADER
    #include <string>
#endif

#define TICK_DURATION 1 / 70.f  // Nombre de secondes écoulées dans la simulation (ie pour le moteur) à chaque appel de stepSimulation
#define TICK_INTERVAL 10000      // Nombre de us séparant deux appels à la méthode stepSimulation

void usage(char * prog);

void moveBot1(struct timeval, Robot *);

void moveBot2(struct timeval, Robot *);

void moveRobudog(struct timeval, Robot *);
 
int main(int argc, char ** argv) {
    
    // Getopt ///////////////////////////////////
    int viewFlag = 0;
    enum {bot1, bot2, robudog} robotName;
    int c;
     
    opterr = 0;

    while ((c = getopt (argc, argv, "vr:")) != -1) {
        switch (c) {
            case 'v':
                viewFlag = 1;
                break;
            case 'r':
                if(strcmp(optarg, "bot1") == 0) {
                    robotName = bot1;
                } else if(strcmp(optarg, "bot2") == 0) {
                    robotName = bot2;
                } else {
                    robotName = robudog;
                }
                break;
            case '?':
                usage(argv[0]);
                return 1;
        }
    }

    // Init simulation //////////////////////////
    World * world = World::createWorld();
    Flat * environment = new Flat();

    Robot * bot;

    switch(robotName) {
        case bot1 :
            bot = new Bot1();
            break;
        case bot2 :
            bot = new Bot2();
            break;
        default :
            bot = new Robudog();
    }

    world->setEnvironment(environment);
    world->setRobot(bot);

    if(viewFlag) {
        OSGView * view = new OSGView();
        view->setWorld(world);
        view->run();
    }

    // Init timers
    struct timeval timev_init;  // Initial absolute time (static)
    struct timeval timev_prev;  // Previous tick absolute time
    struct timeval timev_cur;   // Current tick absolute time
    struct timeval timev_rel;   // Current relative time (curent time - initial time)
    struct timeval timev_diff;  // Tick duration (curent tick time - previous tick time)
    
    timerclear(&timev_init);
    gettimeofday(&timev_init, NULL);

    // First tick
    timev_cur = timev_init;
    world->stepSimulation(TICK_DURATION, 0); // On fait *une* step de 1/100s
    timev_prev = timev_cur;

    // Ticks loop
    while(true) {
        gettimeofday(&timev_cur, NULL);
        timersub(&timev_cur, &timev_prev, &timev_diff);

        // On fait un step de 1/100s toutes les 10000us
        if(timev_diff.tv_usec > TICK_INTERVAL || timev_diff.tv_sec > 0) {

            // Calculate relative time //////////////////////////
            timersub(&timev_cur, &timev_init, &timev_rel);

            // Debug info ///////////////////////////////////////
            //fprintf(stderr, "%02u.%06u : %02u.%06u\n", timev_rel.tv_sec, timev_rel.tv_usec, timev_diff.tv_sec, timev_diff.tv_usec);
            //fprintf(stderr, "%02u.%06u %02f %02f %02f\n", timev_rel.tv_sec, timev_rel.tv_usec, bot->getTrunkTransform("rtleg").getOrigin().getX(), bot->getTrunkTransform("rtleg").getOrigin().getY(), bot->getTrunkTransform("rtleg").getOrigin().getZ());
            std::cout << bot->getTrunk() << std::endl;

            // Move robot ///////////////////////////////////////
            switch(robotName) {
                case bot1 :
                    moveBot1(timev_rel, bot);
                    break;
                case bot2 :
                    moveBot2(timev_rel, bot);
                    break;
                default :
                    moveRobudog(timev_rel, bot);
            }

            // Step simulation ///////////////////////////////////
            world->stepSimulation(TICK_DURATION, 0); // On fait *une* step de 1/100s

            timev_prev = timev_cur;

        }
    }
    
    return 0;
}

void usage(char * prog) {
    fprintf(stderr, "usage: %s [-v] [-r name]\n", prog);
}

void moveBot1(struct timeval timev_cur, Robot * bot) {

    double t = timev_cur.tv_sec + (double) timev_cur.tv_usec / 1000000; // TODO : Approximative cast...

    // Right top hinge //////////////
    double rtHingeVelocity = 1.0 * cos(t * 2 * M_PI * 0.5 + 3.14);                      // a * cos(w * t + d)
    double ltHingeVelocity = 1.0 * cos(t * 2 * M_PI * 0.5 + 3.14);                      // a * cos(w * t + d)
    double rbHingeVelocity = 1.0 * cos(t * 2 * M_PI * 0.5 + 0);                         // a * cos(w * t + d)
    double lbHingeVelocity = 1.0 * cos(t * 2 * M_PI * 0.5 + 0);                         // a * cos(w * t + d)

    bot->getServomotor("rtHinge")->enableAngularMotor(true, rtHingeVelocity, 300.);
    bot->getServomotor("ltHinge")->enableAngularMotor(true, ltHingeVelocity, 300.);
    bot->getServomotor("rbHinge")->enableAngularMotor(true, rbHingeVelocity, 300.);
    bot->getServomotor("lbHinge")->enableAngularMotor(true, lbHingeVelocity, 300.);

}

void moveBot2(struct timeval timev_cur, Robot * bot) {

    double t = timev_cur.tv_sec + (double) timev_cur.tv_usec / 1000000; // TODO : Approximative cast...

    // Right top hinge //////////////
    double rtHingeVelocity = 1.0 * cos(t * 2 * M_PI * 0.5 + 3.14);                      // a * cos(w * t + d)
    double ltHingeVelocity = 1.0 * cos(t * 2 * M_PI * 0.5 + 3.14);                      // a * cos(w * t + d)
    double rbHingeVelocity = 1.0 * cos(t * 2 * M_PI * 0.5 + 0);                         // a * cos(w * t + d)
    double lbHingeVelocity = 1.0 * cos(t * 2 * M_PI * 0.5 + 0);                         // a * cos(w * t + d)

    bot->getServomotor("rtHinge")->enableAngularMotor(true, rtHingeVelocity, 1000.);
    bot->getServomotor("ltHinge")->enableAngularMotor(true, ltHingeVelocity, 1000.);
    bot->getServomotor("rbHinge")->enableAngularMotor(true, rbHingeVelocity, 1000.);
    bot->getServomotor("lbHinge")->enableAngularMotor(true, lbHingeVelocity, 1000.);

}

void moveRobudog(struct timeval timev_cur, Robot * bot) {
    double t = timev_cur.tv_sec + (double) timev_cur.tv_usec / 1000000; // TODO : Approximative cast...

    // Head /////////////////////
    {
    double velocity = 2.0 * cos(t * 2 * M_PI * 0.5 + 3.14);                      // a * cos(w * t + d)
    bot->getServomotor("head_y")->enableAngularMotor(true, velocity, 10000.);
    }

    // Trunk - Clavicle /////////
    /*
    {
    double velocity = 2.0 * cos(t * 2 * M_PI * 0.5 + 3.14);                      // a * cos(w * t + d)
    bot->getServomotor("trunk-left_clavicle")->enableAngularMotor(true, velocity, 100000.);
    }

    {
    double velocity = -2.0 * cos(t * 2 * M_PI * 0.5 + 3.14);               // a * cos(w * t + d)
    bot->getServomotor("trunk-right_clavicle")->enableAngularMotor(true, velocity, 100000.);
    }
    */

    // Clavicle - Shoulder///////
    {
    double velocity = 2.0 * cos(t * 2 * M_PI * 0.5 + 3.14);               // a * cos(w * t + d)
    bot->getServomotor("left_clavicle-shoulder")->enableAngularMotor(true, velocity, 100000.);
    }

    {
    double velocity = -2.0 * cos(t * 2 * M_PI * 0.5 + 3.14);               // a * cos(w * t + d)
    bot->getServomotor("right_clavicle-shoulder")->enableAngularMotor(true, velocity, 100000.);
    }

    // Shoulder - Upper Arm /////
    /*
    {
    double velocity = 2.0 * cos(t * 2 * M_PI * 0.5 + 3.14);               // a * cos(w * t + d)
    bot->getServomotor("left_shoulder-upper_arm")->enableAngularMotor(true, velocity, 100000.);
    }

    {
    double velocity = 2.0 * cos(t * 2 * M_PI * 0.5 + 3.14);               // a * cos(w * t + d)
    bot->getServomotor("right_shoulder-upper_arm")->enableAngularMotor(true, velocity, 100000.);
    }
    */

    // Upper Arm - Fore Arm /////
    {
    double velocity = -2.0 * cos(t * 2 * M_PI * 0.5 + 3.14);               // a * cos(w * t + d)
    bot->getServomotor("left_upper_arm-fore_arm")->enableAngularMotor(true, velocity, 100000.);
    }

    {
    double velocity = -2.0 * cos(t * 2 * M_PI * 0.5 + 3.14);               // a * cos(w * t + d)
    bot->getServomotor("right_upper_arm-fore_arm")->enableAngularMotor(true, velocity, 100000.);
    }

    // Trunk - Hip //////////////
    {
    double velocity = 2.0 * cos(t * 2 * M_PI * 0.5 + 0);                  // a * cos(w * t + d)
    bot->getServomotor("trunk-left_hip")->enableAngularMotor(true, velocity, 100000.);
    }

    {
    double velocity = -2.0 * cos(t * 2 * M_PI * 0.5 + 0);                  // a * cos(w * t + d)
    bot->getServomotor("trunk-right_hip")->enableAngularMotor(true, velocity, 100000.);
    }

    // Hip - Thigh //////////////
    /*
    {
    double velocity = 2.0 * cos(t * 2 * M_PI * 0.5 + 0);                  // a * cos(w * t + d)
    bot->getServomotor("left_hip-left_thigh")->enableAngularMotor(true, velocity, 100000.);
    }

    {
    double velocity = -2.0 * cos(t * 2 * M_PI * 0.5 + 0);                  // a * cos(w * t + d)
    bot->getServomotor("right_hip-right_thigh")->enableAngularMotor(true, velocity, 100000.);
    }
    */

    // Thigh - Shin /////////////
    {
    double velocity = -2.0 * cos(t * 2 * M_PI * 0.5 + 0);                  // a * cos(w * t + d)
    bot->getServomotor("left_thigh-left_shin")->enableAngularMotor(true, velocity, 100000.);
    }

    {
    double velocity = -2.0 * cos(t * 2 * M_PI * 0.5 + 0);                  // a * cos(w * t + d)
    bot->getServomotor("right_thigh-right_shin")->enableAngularMotor(true, velocity, 100000.);
    }

}

