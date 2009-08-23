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

#ifndef ROBOTS_HEADERS
    #define ROBOTS_HEADERS
    #include "Robots.h"
#endif

#ifndef BULLET_HEADERS
    #define BULLET_HEADERS
    #include <btBulletDynamicsCommon.h>
#endif

#ifndef STRING_HEADER
    #define STRING_HEADER
    #include <string>
#endif

#define HEIGHT 1.0f

//#define BODY_X 10.0
//#define BODY_Y 20.0
//#define BODY_Z 5.0
//#define LEG_X 2.0
//#define LEG_Y 2.0
//#define LEG_Z 10.0

Bot1::Bot1() {
    // Bodies ////////////////////////////////////////////////////
    btCollisionShape * bodyShape = new btBoxShape(btVector3(5.0f, 10.0f, 2.5f)); // half lengths
    btCollisionShape * legShape = new btBoxShape(btVector3(1.0f, 1.0f, 5.0f)); // half lengths

    btScalar mass = 10;
    btVector3 inertia(0, 0, 0);
    bodyShape->calculateLocalInertia(mass, inertia);

    //btScalar mass = 7;
    //btVector3 inertia(0, 0, 0);
    legShape->calculateLocalInertia(mass, inertia);

    // Body ///////////////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(mass,
                                                       NULL,
                                                       bodyShape,
                                                       inertia);
    RobotPart * trunk = new RobotPart("trunk", rigidBodyCI);
    trunk->setCenterOfMassTransform(btTransform(btQuaternion(0,0,0,1),
                                   btVector3(0.0f, 0.0f, 9.0f + HEIGHT)));
    setTrunk(trunk);
    }

    // Right top leg //////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(mass,
                                                       NULL,
                                                       legShape,
                                                       inertia);
    RobotPart * rtleg = new RobotPart("rtleg", rigidBodyCI);
    rtleg->setCenterOfMassTransform(btTransform(btQuaternion(0,0,0,1),
                                    btVector3(6.0f, 5.0f, 5.0f + HEIGHT)));
    addPart(rtleg);
    }

    // Left top leg ///////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(mass,
                                                       NULL,
                                                       legShape,
                                                       inertia);
    RobotPart * ltleg = new RobotPart("ltleg", rigidBodyCI);
    ltleg->setCenterOfMassTransform(btTransform(btQuaternion(0,0,0,1),
                                    btVector3(-6.0f ,5.0f ,5.0f + HEIGHT)));
    addPart(ltleg);
    }

    // Right bottom leg ///////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(mass,
                                                       NULL,
                                                       legShape,
                                                       inertia);
    RobotPart * rbleg = new RobotPart("rbleg", rigidBodyCI);
    rbleg->setCenterOfMassTransform(btTransform(btQuaternion(0,0,0,1),
                                    btVector3(6.0f, -5.0f, 5.0f + HEIGHT)));
    addPart(rbleg);
    }

    // Left bottom leg ////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(mass,
                                                       NULL,
                                                       legShape,
                                                       inertia);
    RobotPart * lbleg = new RobotPart("lbleg", rigidBodyCI);
    lbleg->setCenterOfMassTransform(btTransform(btQuaternion(0,0,0,1),
                                    btVector3(-6.0f, -5.0f, 5.0f + HEIGHT)));
    addPart(lbleg);
    }

    // Constraints //////////////////////////////////////////////
    const btVector3 rightLegsPivot( -1.0f, 0.0f, 4.0f );
    const btVector3 leftLegsPivot( 1.0f, 0.0f, 4.0f );

    const btVector3 rtBodyPivot( 5.0f, 5.0f, 0.0f );
    const btVector3 ltBodyPivot( -5.0f, 5.0f, 0.0f );
    const btVector3 rbBodyPivot( 5.0f, -5.0f, 0.0f );
    const btVector3 lbBodyPivot( -5.0f, -5.0f, 0.0f );

    btVector3 hingeAxis( 1.0f, 0.0f, 0.0f ); // TODO : le problème viens peut-être de là... essayer avec un transform plutôt qu'un axe

    Servomotor * rtHinge = new Servomotor("rtHinge",
                                          *getPart("trunk"),
                                          *getPart("rtleg"),
                                          rtBodyPivot,
                                          rightLegsPivot,
                                          hingeAxis,
                                          hingeAxis);

    Servomotor * ltHinge = new Servomotor("ltHinge",
                                          *getPart("trunk"),
                                          *getPart("ltleg"),
                                          ltBodyPivot,
                                          leftLegsPivot,
                                          hingeAxis,
                                          hingeAxis);

    Servomotor * rbHinge = new Servomotor("rbHinge",
                                          *getPart("trunk"),
                                          *getPart("rbleg"),
                                          rbBodyPivot,
                                          rightLegsPivot,
                                          hingeAxis,
                                          hingeAxis);

    Servomotor * lbHinge = new Servomotor("lbHinge",
                                          *getPart("trunk"),
                                          *getPart("lbleg"),
                                          lbBodyPivot,
                                          leftLegsPivot,
                                          hingeAxis,
                                          hingeAxis);
    rtHinge->setAngularOnly(true);
    ltHinge->setAngularOnly(true);
    rbHinge->setAngularOnly(true);
    lbHinge->setAngularOnly(true);

    // default :     (   1,  -1, 0.9, 0.3, 1.0);
    rtHinge->setLimit(-0.2, 0.2, 0.8, 0.2, 0.5);
    ltHinge->setLimit(-0.2, 0.2, 0.8, 0.2, 0.5);
    rbHinge->setLimit(-0.2, 0.2, 0.8, 0.2, 0.5);
    lbHinge->setLimit(-0.2, 0.2, 0.8, 0.2, 0.5);

    addServomotor(rtHinge);
    addServomotor(ltHinge);
    addServomotor(rbHinge);
    addServomotor(lbHinge);
}

