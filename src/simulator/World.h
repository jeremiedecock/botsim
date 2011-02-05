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

#ifndef ENVIRONMENT_HEADERS
	#define  ENVIRONMENT_HEADERS
	#include "Environment.h"
#endif

#ifndef ROBOT_HEADERS
	#define ROBOT_HEADERS
	#include "Robot.h"
#endif

#ifndef BULLET_HEADERS
	#define BULLET_HEADERS
	#include <btBulletDynamicsCommon.h>
#endif

class World : public btDiscreteDynamicsWorld {
private:
	Environment * environment;

	Robot * robot;

public:
	static World * createWorld();

	World(btDispatcher *dispatcher,
          btBroadphaseInterface *pairCache,
          btConstraintSolver *constraintSolver,
          btCollisionConfiguration *collisionConfiguration);

	void setEnvironment(Environment * g);

	void setRobot(Robot * r);

	Environment * getEnvironment();

	Robot * getRobot();
};


