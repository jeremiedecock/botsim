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

#ifndef ROBOT_HEADER
#define ROBOT_HEADER

#include <map>
#include <vector>
#include <string>

#include "RobotPart.h"
#include "Servomotor.h"

class Robot {

    friend std::ostream& operator<< (std::ostream& os, const Robot * robot);

protected:
    static int objectCounter;

    std::string name;

    std::map<std::string, RobotPart *> parts;

    std::map<std::string, Servomotor *> servomotors;

public:
    Robot(std::string name = "Unknown");

    ~Robot();

    std::string getName();

    RobotPart * getTrunk();

    RobotPart * getPart(std::string name);

    std::vector<RobotPart *> getParts();

    Servomotor * getServomotor(std::string name);

    std::vector<Servomotor *> getServomotors();

    void setTrunk(RobotPart * part);

    void addPart(RobotPart * part);
    
    void addServomotor(Servomotor * newServomotor);

    btTransform getTrunkTransform(RobotPart * part);

    btTransform getTrunkTransform(std::string partName);

    bool hasExploded();
};

#endif
