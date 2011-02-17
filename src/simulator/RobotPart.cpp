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

#ifndef ROBOT_PART_HEADERS
	#define ROBOT_PART_HEADERS
	#include "RobotPart.h"
#endif

#include <iostream>

int RobotPart::objectCounter = 0;

std::ostream& operator<< (std::ostream& os, const RobotPart * part) {
   return os << part->getCenterOfMassPosition().getX() << " " << part->getCenterOfMassPosition().getY() << " " << part->getCenterOfMassPosition().getZ();
}

RobotPart::RobotPart(std::string name,
                     const btRigidBodyConstructionInfo& constructionInfo,
                     unsigned short int groupMask,
                     unsigned short int groupMaskInteractWith) : 
                     btRigidBody(constructionInfo),
                     name(name),
                     groupMask(groupMask),
                     groupMaskInteractWith(groupMaskInteractWith) {
    objectCounter++;
    std::cout << "Create robotPart (" << objectCounter << ")" << std::endl;
}

RobotPart::~RobotPart() {
    objectCounter--;
    std::cout << "Remove robotPart (" << objectCounter << ")" << std::endl;
}

std::string RobotPart::getName() {
    return name;
}

unsigned short int RobotPart::getGroupMask() {
    return groupMask;
}

unsigned short int RobotPart::getGroupMaskInteractWith() {
    return groupMaskInteractWith;
}
