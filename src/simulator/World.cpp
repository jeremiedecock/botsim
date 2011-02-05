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

#include "World.h"

#ifndef VECTOR_HEADER
    #define VECTOR_HEADER
    #include <vector>
#endif

#ifndef STRING_HEADER
    #define STRING_HEADER
    #include <string>
#endif

#include <iostream>

World::World(btDispatcher * dispatcher,
             btBroadphaseInterface * broadphase,
             btConstraintSolver * constraintSolver,
             btCollisionConfiguration * collisionConfiguration) :
             btDiscreteDynamicsWorld(dispatcher,
                                     broadphase,
                                     constraintSolver,
                                     collisionConfiguration) {

    std::cout << "Create world" << std::endl;

}

World * World::createWorld() {

    // Init Bullet physics
    btDbvtBroadphase * broadphase = new btDbvtBroadphase();

    btDefaultCollisionConfiguration * collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher * dispatcher = new btCollisionDispatcher(collisionConfiguration);

    btSequentialImpulseConstraintSolver * constraintSolver = new btSequentialImpulseConstraintSolver();

    World * newWorld = new World(dispatcher, broadphase, constraintSolver, collisionConfiguration);

    newWorld->setGravity(btVector3(0, 0, -10));

    return newWorld;

}

void World::setEnvironment(Environment * g) {
    environment = g;

    addRigidBody(environment->getBody(),
                 environment->getBody()->getGroupMask(),
                 environment->getBody()->getGroupMaskInteractWith());
}

void World::setRobot(Robot * r) {
    robot = r;

    // Add robotParts into the world
    std::vector<RobotPart *> robotParts = robot->getParts();
    std::vector<RobotPart *>::iterator it1;

    for(it1 = robotParts.begin() ; it1 != robotParts.end() ; it1++) {
        addRigidBody(*it1,
                     (*it1)->getGroupMask(),
                     (*it1)->getGroupMaskInteractWith());
    }

    // Add servomotors into the world
    std::vector<Servomotor *> servomotors = robot->getServomotors();
    std::vector<Servomotor *>::iterator it2;

    for(it2 = servomotors.begin() ; it2 != servomotors.end() ; it2++) {
        addConstraint(*it2);
    }
}

Environment * World::getEnvironment() {
    return environment;
}

Robot * World::getRobot() {
    return robot;
}

