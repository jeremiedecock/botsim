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

#ifndef ROBOT_HEADERS
    #define ROBOT_HEADERS
    #include "Robot.h"
#endif

#include <iostream>

#include <string>

int Robot::objectCounter = 0;

std::ostream& operator<< (std::ostream& os, const Robot * robot) {
   //float x = robot->getTrunk()->getCenterOfMassPosition().getX();
   //float y = robot->getTrunk()->getCenterOfMassPosition().getY();

   //float dist =  // TODO : distance à l'origine
   
   //return os << x << " " << y;
   return os;
}

Robot::Robot(std::string name) {
    objectCounter++;
    std::cout << "Create robot (" << objectCounter << ")" << std::endl;
}

Robot::~Robot() {
    objectCounter--;
    std::cout << "Remove robot (" << objectCounter << ")" << std::endl;
}

std::string Robot::getName() {
    return name;
}

RobotPart * Robot::getTrunk() {
    if(parts["trunk"] == NULL) {
        std::cout << "Error : there are no robot part named \"Trunk\" in " << getName() << std::endl;
        exit(1);
    }
    return parts["trunk"];
}

RobotPart * Robot::getPart(std::string name) {
    if(parts[name] == NULL) {
        std::cout << "Error : there are no robot part named \"" << name << "\" in " << getName() << std::endl;
        exit(1);
    }
    return parts[name];
}

std::vector<RobotPart *> Robot::getParts() {
    std::vector<RobotPart *> partsVector;

    std::map<std::string, RobotPart *>::iterator it;
    for(it = parts.begin() ; it != parts.end() ; it++) {
        RobotPart * robotPart = (*it).second;
        partsVector.push_back(robotPart);
    }

    return partsVector;
}

Servomotor * Robot::getServomotor(std::string name) {
    if(servomotors[name] == NULL) {
        std::cout << "Error : there are no servomotor named \"" << name << "\" in " << getName() << std::endl;
        exit(1);
    }
    return servomotors[name];
}

std::vector<Servomotor *> Robot::getServomotors() {
    std::vector<Servomotor *> servomotorVector;

    std::map<std::string, Servomotor *>::iterator it;
    for(it = servomotors.begin() ; it != servomotors.end() ; it++) {
        Servomotor * servomotor = (*it).second;
        servomotorVector.push_back(servomotor);
    }

    return servomotorVector;
}

void Robot::setTrunk(RobotPart * newPart) {
    parts["trunk"] = newPart;
}

void Robot::addPart(RobotPart * newPart) {
    parts[newPart->getName()] = newPart;
}

void Robot::addServomotor(Servomotor * newServomotor) {
    servomotors[newServomotor->getName()] = newServomotor;
}

btTransform Robot::getTrunkTransform(RobotPart * part) {
    // TODO : check this function...
    btTransform trunkTransform = getTrunk()->getWorldTransform();
    btTransform partTransform = part->getWorldTransform();

    btVector3 diffOrigin = (trunkTransform.getOrigin() - partTransform.getOrigin()).absolute();
    btQuaternion diffRotation = trunkTransform.getRotation() - partTransform.getRotation();

    return btTransform(diffRotation, diffOrigin);
}

btTransform Robot::getTrunkTransform(std::string partName) {
   return getTrunkTransform(getPart(partName)); 
}

bool Robot::hasExploded() {
    // TODO : implement this function
    return false;
}
