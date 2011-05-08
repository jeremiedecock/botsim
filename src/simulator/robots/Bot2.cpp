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

#include <btBulletDynamicsCommon.h>
#include <string>

#include "Bot2.h"

#define HEIGHT 1.0f

#define HALF_TRUNK_SIZE_X 50.0f
#define HALF_TRUNK_SIZE_Y 100.0f
#define HALF_TRUNK_SIZE_Z 25.0f
#define HALF_LEG_SIZE_X 10.0f
#define HALF_LEG_SIZE_Y 10.0f
#define HALF_LEG_SIZE_Z 50.0f

Bot2::Bot2() {

    name = "bot2";

    // Bodies ////////////////////////////////////////////////////
    btCollisionShape * trunkShape = new btBoxShape(btVector3(HALF_TRUNK_SIZE_X, HALF_TRUNK_SIZE_Y, HALF_TRUNK_SIZE_Z)); // half lengths
    btCollisionShape * legShape = new btBoxShape(btVector3(HALF_LEG_SIZE_X, HALF_LEG_SIZE_Y, HALF_LEG_SIZE_Z));        // half lengths

    btScalar trunkMass = 50;
    btVector3 trunkInertia(0, 0, 0);
    trunkShape->calculateLocalInertia(trunkMass, trunkInertia);

    btScalar legMass = 25;
    btVector3 legInertia(0, 0, 0);
    legShape->calculateLocalInertia(legMass, legInertia);

    // Trunk //////////////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(trunkMass,
                                                       NULL,
                                                       trunkShape,
                                                       trunkInertia);
    RobotPart * trunk = new RobotPart("trunk", rigidBodyCI);

    trunk->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                   btVector3(0.0f,
                                             0.0f,
                                             HALF_LEG_SIZE_Z * 2.0f - HALF_LEG_SIZE_X + HEIGHT)));

    setTrunk(trunk);
    }

    // Right top leg //////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(legMass,
                                                       NULL,
                                                       legShape,
                                                       legInertia);
    RobotPart * rtleg = new RobotPart("rtleg", rigidBodyCI);

    rtleg->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                    btVector3(HALF_TRUNK_SIZE_X + HALF_LEG_SIZE_X,
                                              HALF_TRUNK_SIZE_Y - (2.0f * HALF_LEG_SIZE_Y),
                                              HALF_LEG_SIZE_Z + HEIGHT)));
    //rtleg->setFriction(5.0);

    addPart(rtleg);
    }

    // Left top leg ///////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(legMass,
                                                       NULL,
                                                       legShape,
                                                       legInertia);
    RobotPart * ltleg = new RobotPart("ltleg", rigidBodyCI);

    ltleg->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                    btVector3(-(HALF_TRUNK_SIZE_X + HALF_LEG_SIZE_X),
                                              HALF_TRUNK_SIZE_Y - (2.0f * HALF_LEG_SIZE_Y),
                                              HALF_LEG_SIZE_Z + HEIGHT)));
    //ltleg->setFriction(5.0);

    addPart(ltleg);
    }

    // Right bottom leg ///////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(legMass,
                                                       NULL,
                                                       legShape,
                                                       legInertia);
    RobotPart * rbleg = new RobotPart("rbleg", rigidBodyCI);

    rbleg->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                    btVector3(HALF_TRUNK_SIZE_X + HALF_LEG_SIZE_X,
                                              -(HALF_TRUNK_SIZE_Y - (2.0f * HALF_LEG_SIZE_Y)),
                                              HALF_LEG_SIZE_Z + HEIGHT)));
    //rbleg->setFriction(5.0);

    addPart(rbleg);
    }

    // Left bottom leg ////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(legMass,
                                                       NULL,
                                                       legShape,
                                                       legInertia);
    RobotPart * lbleg = new RobotPart("lbleg", rigidBodyCI);

    lbleg->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                    btVector3(-(HALF_TRUNK_SIZE_X + HALF_LEG_SIZE_X),
                                              -(HALF_TRUNK_SIZE_Y - (2.0f * HALF_LEG_SIZE_Y)),
                                              HALF_LEG_SIZE_Z + HEIGHT)));
    //lbleg->setFriction(5.0);

    addPart(lbleg);
    }

    // Constraints //////////////////////////////////////////////
    const btVector3 rightLegsPivot( -HALF_LEG_SIZE_X, 0.0f, HALF_LEG_SIZE_Z - HALF_LEG_SIZE_X );
    const btVector3 leftLegsPivot(   HALF_LEG_SIZE_X, 0.0f, HALF_LEG_SIZE_Z - HALF_LEG_SIZE_X );

    const btVector3 rtBodyPivot(  HALF_TRUNK_SIZE_X,   HALF_TRUNK_SIZE_Y - (2.0f * HALF_LEG_SIZE_Y),  0.0f );
    const btVector3 ltBodyPivot( -HALF_TRUNK_SIZE_X,   HALF_TRUNK_SIZE_Y - (2.0f * HALF_LEG_SIZE_Y),  0.0f );
    const btVector3 rbBodyPivot(  HALF_TRUNK_SIZE_X, -(HALF_TRUNK_SIZE_Y - (2.0f * HALF_LEG_SIZE_Y)), 0.0f );
    const btVector3 lbBodyPivot( -HALF_TRUNK_SIZE_X, -(HALF_TRUNK_SIZE_Y - (2.0f * HALF_LEG_SIZE_Y)), 0.0f );

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

Bot2::~Bot2() {
    // TODO : delete
}

