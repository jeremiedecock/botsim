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

#include <iostream>

#include "Servomotor.h"

int Servomotor::objectCounter = 0;

Servomotor::Servomotor(std::string name,
                       btRigidBody& rbA,
                       btRigidBody& rbB,
                       const btVector3& pivotInA,
                       const btVector3& pivotInB,
                       btVector3& axisInA,
                       btVector3& axisInB,
                       bool useReferenceFrameA) :
                       btHingeConstraint(rbA, 
                                         rbB,
                                         pivotInA,
                                         pivotInB,
                                         axisInA,
                                         axisInB,
                                         useReferenceFrameA),
                       name(name) {
    objectCounter++;
    std::cout << "Create servomotor (" << objectCounter << ")" << std::endl;
}

Servomotor::~Servomotor() {
    objectCounter--;
    std::cout << "Remove servomotor (" << objectCounter << ")" << std::endl;
}

std::string Servomotor::getName() {
    return name;
}

void Servomotor::setDesiredAngle(float desiredAngle) {
    // TODO : ...
    //getHingeAngle();
    //getLowerLimit();
    //getUpperLimit();

    //if() setLimit();
    //else setLimit();
}

