/*
 * Copyright (c) 2008,2009,2011 Jérémie DECOCK <webmaster@jdhp.org>
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
    { // 1
    double velocity = -M_PI/2. * sin(t * M_PI + M_PI);               // a * cos(w * t + d)
    bot->getServomotor("left_clavicle-shoulder")->enableAngularMotor(true, velocity, 5000.);
    }

    { // 2
    double velocity = -M_PI/2. * sin(t * M_PI);               // a * cos(w * t + d)
    bot->getServomotor("right_clavicle-shoulder")->enableAngularMotor(true, velocity, 5000.);
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
    { // 3
    double velocity = M_PI/2. * sin(t * M_PI);               // a * cos(w * t + d)
    bot->getServomotor("left_upper_arm-fore_arm")->enableAngularMotor(true, velocity, 5000.);
    }

    { // 4
    double velocity = M_PI/2. * sin(t * M_PI + M_PI);               // a * cos(w * t + d)
    bot->getServomotor("right_upper_arm-fore_arm")->enableAngularMotor(true, velocity, 5000.);
    }

    // Trunk - Hip //////////////
    { // 5
    double velocity = -M_PI/2. * sin(t * M_PI + M_PI);               // a * cos(w * t + d)
    bot->getServomotor("trunk-left_hip")->enableAngularMotor(true, velocity, 5000.);
    }

    { // 6
    double velocity = -M_PI/2. * sin(t * M_PI);               // a * cos(w * t + d)
    bot->getServomotor("trunk-right_hip")->enableAngularMotor(true, velocity, 5000.);
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
    { // 7
    double velocity = M_PI/2. * sin(t * M_PI);               // a * cos(w * t + d)
    bot->getServomotor("left_thigh-left_shin")->enableAngularMotor(true, velocity, 5000.);
    }

    { // 8
    double velocity = M_PI/2. * sin(t * M_PI + M_PI);               // a * cos(w * t + d)
    bot->getServomotor("right_thigh-right_shin")->enableAngularMotor(true, velocity, 5000.);
    }

}

