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

#define HALF_TRUNK_SIZE_X 90.0f  ///
#define HALF_TRUNK_SIZE_Y 40.0f  ///
#define HALF_TRUNK_SIZE_Z 40.0f  ///

#define HALF_CLAVICLE_SIZE_X 10.0f  ///
#define HALF_CLAVICLE_SIZE_Y 10.0f  ///
#define HALF_CLAVICLE_SIZE_Z 10.0f  ///

#define HALF_SHOULDER_SIZE_X 10.0f  ///
#define HALF_SHOULDER_SIZE_Y 10.0f  ///
#define HALF_SHOULDER_SIZE_Z 10.0f  ///

#define HALF_UPPER_ARM_SIZE_X 10.0f  ///
#define HALF_UPPER_ARM_SIZE_Y 10.0f  ///
#define HALF_UPPER_ARM_SIZE_Z 20.0f

#define HALF_FORE_ARM_SIZE_X 10.0f  ///
#define HALF_FORE_ARM_SIZE_Y 10.0f  ///
#define HALF_FORE_ARM_SIZE_Z 20.0f

#define HALF_HIP_SIZE_X 10.0f  ///
#define HALF_HIP_SIZE_Y 10.0f  ///
#define HALF_HIP_SIZE_Z 10.0f  ///

#define HALF_THIGH_SIZE_X 10.0f  ///
#define HALF_THIGH_SIZE_Y 10.0f  ///
#define HALF_THIGH_SIZE_Z 20.0f

#define HALF_SHIN_SIZE_X 10.0f  ///
#define HALF_SHIN_SIZE_Y 10.0f  ///
#define HALF_SHIN_SIZE_Z 20.0f

#define HEAD_RADIUS 40.0f

#define FOOT_RADIUS 15.0f  ///

Robudog::Robudog() {
    name = "robudog";

    // Robot Parts ////////////////////////////////////////////////////
    btCollisionShape * trunkShape = new btBoxShape(btVector3(HALF_TRUNK_SIZE_X, HALF_TRUNK_SIZE_Y, HALF_TRUNK_SIZE_Z));                // half lengths
    btCollisionShape * clavicleShape = new btBoxShape(btVector3(HALF_CLAVICLE_SIZE_X, HALF_CLAVICLE_SIZE_Y, HALF_CLAVICLE_SIZE_Z));    // half lengths
    btCollisionShape * shoulderShape = new btBoxShape(btVector3(HALF_SHOULDER_SIZE_X, HALF_SHOULDER_SIZE_Y, HALF_SHOULDER_SIZE_Z));    // half lengths
    btCollisionShape * upperArmShape = new btBoxShape(btVector3(HALF_UPPER_ARM_SIZE_X, HALF_UPPER_ARM_SIZE_Y, HALF_UPPER_ARM_SIZE_Z)); // half lengths
    btCollisionShape * foreArmShape = new btBoxShape(btVector3(HALF_FORE_ARM_SIZE_X, HALF_FORE_ARM_SIZE_Y, HALF_FORE_ARM_SIZE_Z));     // half lengths
    btCollisionShape * hipShape  = new btBoxShape(btVector3(HALF_HIP_SIZE_X, HALF_HIP_SIZE_Y, HALF_HIP_SIZE_Z));                       // half lengths
    btCollisionShape * thighShape = new btBoxShape(btVector3(HALF_THIGH_SIZE_X, HALF_THIGH_SIZE_Y, HALF_THIGH_SIZE_Z));                // half lengths
    btCollisionShape * shinShape = new btBoxShape(btVector3(HALF_SHIN_SIZE_X, HALF_SHIN_SIZE_Y, HALF_SHIN_SIZE_Z));                    // half lengths
    btCollisionShape * footShape = new btSphereShape(FOOT_RADIUS);                                                                     // radius
    btCollisionShape * headShape = new btSphereShape(HEAD_RADIUS);                                                                     // radius

    //btScalar trunkMass = 70;
    btScalar trunkMass = 350;
    //btScalar trunkMass = 0;
    btVector3 trunkInertia(0, 0, 0);
    trunkShape->calculateLocalInertia(trunkMass, trunkInertia);

    btScalar clavicleMass = 5;
    btVector3 clavicleInertia(0, 0, 0);
    clavicleShape->calculateLocalInertia(clavicleMass, clavicleInertia);

    btScalar shoulderMass = 5;
    btVector3 shoulderInertia(0, 0, 0);
    shoulderShape->calculateLocalInertia(shoulderMass, shoulderInertia);

    btScalar upperArmMass = 10;
    btVector3 upperArmInertia(0, 0, 0);
    upperArmShape->calculateLocalInertia(upperArmMass, upperArmInertia);

    btScalar foreArmMass = 10;
    btVector3 foreArmInertia(0, 0, 0);
    foreArmShape->calculateLocalInertia(foreArmMass, foreArmInertia);

    btScalar hipMass = 5;
    btVector3 hipInertia(0, 0, 0);
    hipShape->calculateLocalInertia(hipMass, hipInertia);

    btScalar thighMass = 12;
    btVector3 thighInertia(0, 0, 0);
    thighShape->calculateLocalInertia(thighMass, thighInertia);

    btScalar shinMass = 12;
    btVector3 shinInertia(0, 0, 0);
    shinShape->calculateLocalInertia(shinMass, shinInertia);

    btScalar footMass = 2;
    btVector3 footInertia(0, 0, 0);
    footShape->calculateLocalInertia(footMass, footInertia);

    btScalar headMass = 5;
    btVector3 headInertia(0, 0, 0);
    headShape->calculateLocalInertia(headMass, headInertia);

    // Trunk ////////////////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(trunkMass,
                                                       NULL,
                                                       trunkShape,
                                                       trunkInertia);
    RobotPart * trunk = new RobotPart("trunk", rigidBodyCI);

    trunk->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                    btVector3(0.0f,
                                              0.0f,
                                              FOOT_RADIUS * 2.0f + HALF_FORE_ARM_SIZE_Z * 2.0f + HALF_UPPER_ARM_SIZE_Z * 2.0f + HALF_TRUNK_SIZE_Z + HEIGHT)));

    setTrunk(trunk);
    }

    // Head /////////////////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(headMass,
                                                       NULL,
                                                       headShape,
                                                       headInertia);
    RobotPart * part = new RobotPart("head", rigidBodyCI);

    part->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                   btVector3( HALF_TRUNK_SIZE_X,
                                              0.0f,
                                              FOOT_RADIUS * 2.0f + HALF_FORE_ARM_SIZE_Z * 2.0f + HALF_UPPER_ARM_SIZE_Z * 2.0f + HALF_TRUNK_SIZE_Z * 2.0f + HEAD_RADIUS + HEIGHT)));
    part->setFriction(0.5);

    addPart(part);
    }

    // Left clavicle ////////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(clavicleMass,
                                                       NULL,
                                                       clavicleShape,
                                                       clavicleInertia);
    RobotPart * part = new RobotPart("left_clavicle", rigidBodyCI);

    part->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                   btVector3( HALF_TRUNK_SIZE_X - (3.0f * HALF_CLAVICLE_SIZE_X),
                                              HALF_TRUNK_SIZE_Y + HALF_CLAVICLE_SIZE_Y,
                                              FOOT_RADIUS * 2.0f + HALF_FORE_ARM_SIZE_Z * 2.0f + HALF_UPPER_ARM_SIZE_Z * 2.0f + HALF_SHOULDER_SIZE_Z + HEIGHT)));
    part->setFriction(0.5);

    addPart(part);
    }

    // Right clavicle ///////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(clavicleMass,
                                                       NULL,
                                                       clavicleShape,
                                                       clavicleInertia);
    RobotPart * part = new RobotPart("right_clavicle", rigidBodyCI);

    part->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                   btVector3( HALF_TRUNK_SIZE_X - (3.0f * HALF_CLAVICLE_SIZE_X),
                                              -(HALF_TRUNK_SIZE_Y + HALF_CLAVICLE_SIZE_Y),
                                              FOOT_RADIUS * 2.0f + HALF_FORE_ARM_SIZE_Z * 2.0f + HALF_UPPER_ARM_SIZE_Z * 2.0f + HALF_SHOULDER_SIZE_Z + HEIGHT)));
    part->setFriction(0.5);

    addPart(part);
    }

    // Left shoulder ////////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(shoulderMass,
                                                       NULL,
                                                       shoulderShape,
                                                       shoulderInertia);
    RobotPart * part = new RobotPart("left_shoulder", rigidBodyCI);

    part->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                   btVector3( HALF_TRUNK_SIZE_X - (3.0f * HALF_CLAVICLE_SIZE_X),
                                              HALF_TRUNK_SIZE_Y + HALF_CLAVICLE_SIZE_Y * 2.0f + HALF_SHOULDER_SIZE_Y,
                                              FOOT_RADIUS * 2.0f + HALF_FORE_ARM_SIZE_Z * 2.0f + HALF_UPPER_ARM_SIZE_Z * 2.0f + HALF_SHOULDER_SIZE_Z + HEIGHT)));
    part->setFriction(0.5);

    addPart(part);
    }

    // Right shoulder ///////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(shoulderMass,
                                                       NULL,
                                                       shoulderShape,
                                                       shoulderInertia);
    RobotPart * part = new RobotPart("right_shoulder", rigidBodyCI);

    part->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                   btVector3( HALF_TRUNK_SIZE_X - (3.0f * HALF_CLAVICLE_SIZE_X),
                                              -(HALF_TRUNK_SIZE_Y + HALF_CLAVICLE_SIZE_Y * 2.0f + HALF_SHOULDER_SIZE_Y),
                                              FOOT_RADIUS * 2.0f + HALF_FORE_ARM_SIZE_Z * 2.0f + HALF_UPPER_ARM_SIZE_Z * 2.0f + HALF_SHOULDER_SIZE_Z + HEIGHT)));
    part->setFriction(0.5);

    addPart(part);
    }

    // Left upper arm ///////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(upperArmMass,
                                                       NULL,
                                                       upperArmShape,
                                                       upperArmInertia);
    RobotPart * part = new RobotPart("left_upper_arm", rigidBodyCI);

    part->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                   btVector3( HALF_TRUNK_SIZE_X - (3.0f * HALF_CLAVICLE_SIZE_X),
                                              HALF_TRUNK_SIZE_Y + HALF_CLAVICLE_SIZE_Y * 2.0f + HALF_SHOULDER_SIZE_Y,
                                              FOOT_RADIUS * 2.0f + HALF_FORE_ARM_SIZE_Z * 2.0f + HALF_UPPER_ARM_SIZE_Z + HEIGHT)));
    part->setFriction(0.5);

    addPart(part);
    }

    // Right upper arm //////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(upperArmMass,
                                                       NULL,
                                                       upperArmShape,
                                                       upperArmInertia);
    RobotPart * part = new RobotPart("right_upper_arm", rigidBodyCI);

    part->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                   btVector3( HALF_TRUNK_SIZE_X - (3.0f * HALF_CLAVICLE_SIZE_X),
                                              -(HALF_TRUNK_SIZE_Y + HALF_CLAVICLE_SIZE_Y * 2.0f + HALF_SHOULDER_SIZE_Y),
                                              FOOT_RADIUS * 2.0f + HALF_FORE_ARM_SIZE_Z * 2.0f + HALF_UPPER_ARM_SIZE_Z + HEIGHT)));
    part->setFriction(0.5);

    addPart(part);
    }

    // Left fore arm ////////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(foreArmMass,
                                                       NULL,
                                                       foreArmShape,
                                                       foreArmInertia);
    RobotPart * part = new RobotPart("left_fore_arm", rigidBodyCI);

    part->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                   btVector3( HALF_TRUNK_SIZE_X - (3.0f * HALF_CLAVICLE_SIZE_X),
                                              HALF_TRUNK_SIZE_Y + HALF_CLAVICLE_SIZE_Y * 2.0f + HALF_SHOULDER_SIZE_Y,
                                              FOOT_RADIUS * 2.0f + HALF_FORE_ARM_SIZE_Z + HEIGHT)));
    part->setFriction(0.5);

    addPart(part);
    }

    // Right fore arm ///////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(foreArmMass,
                                                       NULL,
                                                       foreArmShape,
                                                       foreArmInertia);
    RobotPart * part = new RobotPart("right_fore_arm", rigidBodyCI);

    part->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                   btVector3( HALF_TRUNK_SIZE_X - (3.0f * HALF_CLAVICLE_SIZE_X),
                                              -(HALF_TRUNK_SIZE_Y + HALF_CLAVICLE_SIZE_Y * 2.0f + HALF_SHOULDER_SIZE_Y),
                                              FOOT_RADIUS * 2.0f + HALF_FORE_ARM_SIZE_Z + HEIGHT)));
    part->setFriction(0.5);

    addPart(part);
    }

    // Left fore foot ///////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(footMass,
                                                       NULL,
                                                       footShape,
                                                       footInertia);
    RobotPart * part = new RobotPart("left_fore_foot", rigidBodyCI);

    part->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                   btVector3( HALF_TRUNK_SIZE_X - (3.0f * HALF_CLAVICLE_SIZE_X),
                                              HALF_TRUNK_SIZE_Y + HALF_CLAVICLE_SIZE_Y * 2.0f + HALF_SHOULDER_SIZE_Y,
                                              FOOT_RADIUS + HEIGHT)));
    part->setFriction(4.0);

    addPart(part);
    }

    // Right fore foot //////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(footMass,
                                                       NULL,
                                                       footShape,
                                                       footInertia);
    RobotPart * part = new RobotPart("right_fore_foot", rigidBodyCI);

    part->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                   btVector3( HALF_TRUNK_SIZE_X - (3.0f * HALF_CLAVICLE_SIZE_X),
                                              -(HALF_TRUNK_SIZE_Y + HALF_CLAVICLE_SIZE_Y * 2.0f + HALF_SHOULDER_SIZE_Y),
                                              FOOT_RADIUS + HEIGHT)));
    part->setFriction(4.0);

    addPart(part);
    }

    // Left hip /////////////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(hipMass,
                                                       NULL,
                                                       hipShape,
                                                       hipInertia);
    RobotPart * part = new RobotPart("left_hip", rigidBodyCI);

    part->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                   btVector3( -(HALF_TRUNK_SIZE_X - HALF_HIP_SIZE_X),
                                              HALF_TRUNK_SIZE_Y + HALF_HIP_SIZE_Y,
                                              FOOT_RADIUS * 2.0f + HALF_SHIN_SIZE_Z * 2.0f + HALF_THIGH_SIZE_Z * 2.0f + HALF_HIP_SIZE_Z + HEIGHT)));
    part->setFriction(0.5);

    addPart(part);
    }

    // Right hip ////////////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(hipMass,
                                                       NULL,
                                                       hipShape,
                                                       hipInertia);
    RobotPart * part = new RobotPart("right_hip", rigidBodyCI);

    part->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                   btVector3( -(HALF_TRUNK_SIZE_X - HALF_HIP_SIZE_X),
                                              -(HALF_TRUNK_SIZE_Y + HALF_HIP_SIZE_Y),
                                              FOOT_RADIUS * 2.0f + HALF_SHIN_SIZE_Z * 2.0f + HALF_THIGH_SIZE_Z * 2.0f + HALF_HIP_SIZE_Z + HEIGHT)));
    part->setFriction(0.5);

    addPart(part);
    }

    // Left thigh ///////////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(thighMass,
                                                       NULL,
                                                       thighShape,
                                                       thighInertia);
    RobotPart * part = new RobotPart("left_thigh", rigidBodyCI);

    part->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                   btVector3( -(HALF_TRUNK_SIZE_X - HALF_HIP_SIZE_X),
                                              HALF_TRUNK_SIZE_Y + HALF_HIP_SIZE_Y,
                                              FOOT_RADIUS * 2.0f + HALF_SHIN_SIZE_Z * 2.0f + HALF_THIGH_SIZE_Z + HEIGHT)));
    part->setFriction(0.5);

    addPart(part);
    }

    // Right thigh //////////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(thighMass,
                                                       NULL,
                                                       thighShape,
                                                       thighInertia);
    RobotPart * part = new RobotPart("right_thigh", rigidBodyCI);

    part->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                   btVector3( -(HALF_TRUNK_SIZE_X - HALF_HIP_SIZE_X),
                                              -(HALF_TRUNK_SIZE_Y + HALF_HIP_SIZE_Y),
                                              FOOT_RADIUS * 2.0f + HALF_SHIN_SIZE_Z * 2.0f + HALF_THIGH_SIZE_Z + HEIGHT)));
    part->setFriction(0.5);

    addPart(part);
    }

    // Left shin ////////////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(shinMass,
                                                       NULL,
                                                       shinShape,
                                                       shinInertia);
    RobotPart * part = new RobotPart("left_shin", rigidBodyCI);

    part->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                   btVector3( -(HALF_TRUNK_SIZE_X - HALF_HIP_SIZE_X),
                                              HALF_TRUNK_SIZE_Y + HALF_HIP_SIZE_Y,
                                              FOOT_RADIUS * 2.0f + HALF_SHIN_SIZE_Z + HEIGHT)));
    part->setFriction(0.5);

    addPart(part);
    }

    // Right shin ///////////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(shinMass,
                                                       NULL,
                                                       shinShape,
                                                       shinInertia);
    RobotPart * part = new RobotPart("right_shin", rigidBodyCI);

    part->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                   btVector3( -(HALF_TRUNK_SIZE_X - HALF_HIP_SIZE_X),
                                              -(HALF_TRUNK_SIZE_Y + HALF_HIP_SIZE_Y),
                                              FOOT_RADIUS * 2.0f + HALF_SHIN_SIZE_Z + HEIGHT)));
    part->setFriction(0.5);

    addPart(part);
    }

    // Left hind foot ///////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(footMass,
                                                       NULL,
                                                       footShape,
                                                       footInertia);
    RobotPart * part = new RobotPart("left_hind_foot", rigidBodyCI);

    part->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                   btVector3( -(HALF_TRUNK_SIZE_X - HALF_HIP_SIZE_X),
                                              HALF_TRUNK_SIZE_Y + HALF_HIP_SIZE_Y,
                                              FOOT_RADIUS + HEIGHT)));
    part->setFriction(4.0);

    addPart(part);
    }

    // Right hind foot //////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(footMass,
                                                       NULL,
                                                       footShape,
                                                       footInertia);
    RobotPart * part = new RobotPart("right_hind_foot", rigidBodyCI);

    part->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                   btVector3( -(HALF_TRUNK_SIZE_X - HALF_HIP_SIZE_X),
                                              -(HALF_TRUNK_SIZE_Y + HALF_HIP_SIZE_Y),
                                              FOOT_RADIUS + HEIGHT)));
    part->setFriction(4.0);

    addPart(part);
    }

/*
    // xxx //////////////////////
    {
    RobotPart::btRigidBodyConstructionInfo rigidBodyCI(xxxMass,
                                                       NULL,
                                                       xxxShape,
                                                       xxxInertia);
    RobotPart * part = new RobotPart("xxx", rigidBodyCI);

    part->setCenterOfMassTransform(btTransform(btQuaternion(0, 0, 0, 1),
                                   btVector3( ,
                                              ,
                                              + HEIGHT)));
    //part->setFriction(5.0);

    addPart(part);
    }
*/

    // Constraints //////////////////////////////////////////////

    // Trunk pivots /////////////
    const btVector3 trunkToLeftClaviclePivot( HALF_TRUNK_SIZE_X - (3.0f * HALF_CLAVICLE_SIZE_X),
                                              HALF_TRUNK_SIZE_Y,
                                              -HALF_TRUNK_SIZE_Z + HALF_CLAVICLE_SIZE_Z);

    const btVector3 trunkToRightClaviclePivot( HALF_TRUNK_SIZE_X - (3.0f * HALF_CLAVICLE_SIZE_X),
                                               -HALF_TRUNK_SIZE_Y,
                                               -HALF_TRUNK_SIZE_Z + HALF_CLAVICLE_SIZE_Z);

    const btVector3 trunkToLeftHipPivot( -(HALF_TRUNK_SIZE_X - HALF_HIP_SIZE_X),
                                         HALF_TRUNK_SIZE_Y,
                                         -HALF_TRUNK_SIZE_Z + HALF_HIP_SIZE_Z);

    const btVector3 trunkToRightHipPivot( -(HALF_TRUNK_SIZE_X - HALF_HIP_SIZE_X),
                                          -HALF_TRUNK_SIZE_Y,
                                          -HALF_TRUNK_SIZE_Z + HALF_HIP_SIZE_Z);

    const btVector3 trunkToHeadPivot( HALF_TRUNK_SIZE_X,
                                      0.0f,
                                      HALF_TRUNK_SIZE_Z );

    // Head pivot ///////////////
    const btVector3 headPivot( 0.0f, 0.0f, -HEAD_RADIUS );

    // Left clavicle pivots /////
    const btVector3 leftClavicleToTrunkPivot(    0.0f,   -HALF_CLAVICLE_SIZE_Y,  0.0f );
    const btVector3 leftClavicleToShoulderPivot( 0.0f,   HALF_CLAVICLE_SIZE_Y,   0.0f );

    // Right clavicle pivots ////
    const btVector3 rightClavicleToTrunkPivot(    0.0f,   HALF_CLAVICLE_SIZE_Y,  0.0f );
    const btVector3 rightClavicleToShoulderPivot( 0.0f,   -HALF_CLAVICLE_SIZE_Y,  0.0f );

    // Shoulder pivots //////////
    const btVector3 leftShoulderToClaviclePivot(  0.0f,  -HALF_SHOULDER_SIZE_Y,  0.0f );
    const btVector3 rightShoulderToClaviclePivot( 0.0f,  HALF_SHOULDER_SIZE_Y,   0.0f );
    const btVector3 shoulderToUpperArmPivot(      0.0f,  0.0f,                  -HALF_SHOULDER_SIZE_Z );

    // Upper arm pivots /////////
    const btVector3 upperArmToShoulderPivot( 0.0f,  0.0f,  HALF_UPPER_ARM_SIZE_Z );
    const btVector3 upperArmToForeArmPivot(  0.0f,  0.0f,  -HALF_UPPER_ARM_SIZE_Z );

    // Fore arm pivots //////////
    const btVector3 foreArmToUpperArmPivot( 0.0f,  0.0f,  HALF_FORE_ARM_SIZE_Z );
    const btVector3 foreArmToFootPivot(     0.0f,  0.0f,  -HALF_FORE_ARM_SIZE_Z );

    // Hip pivots ///////////////
    const btVector3 leftHipToTrunkPivot(  0.0f,  -HALF_HIP_SIZE_Y,  0.0f );
    const btVector3 rightHipToTrunkPivot( 0.0f,  HALF_HIP_SIZE_Y,   0.0f );
    const btVector3 hipToThighPivot(      0.0f,  0.0f,              -HALF_HIP_SIZE_Z );

    // Thigh pivots /////////////
    const btVector3 thighToHipPivot(  0.0f,  0.0f,  HALF_THIGH_SIZE_Z );
    const btVector3 thighToShinPivot( 0.0f,  0.0f,  -HALF_THIGH_SIZE_Z );

    // Shin pivots //////////////
    const btVector3 shinToThighPivot( 0.0f,  0.0f,  HALF_SHIN_SIZE_Z );
    const btVector3 shinToFootPivot(  0.0f,  0.0f,  -HALF_SHIN_SIZE_Z );

    // Foot pivot ///////////////
    const btVector3 footPivot( 0.0f,  0.0f,  FOOT_RADIUS );


    // Axis /////////////////////
    btVector3 xAxis( 1.0f, 0.0f, 0.0f );
    btVector3 yAxis( 0.0f, 1.0f, 0.0f );
    btVector3 zAxis( 0.0f, 0.0f, 1.0f );


    // Head /////////////////////
    {
    Servomotor * servomotor = new Servomotor("head_y",
                                             *getPart("trunk"),
                                             *getPart("head"),
                                             trunkToHeadPivot,
                                             headPivot,
                                             yAxis,
                                             yAxis);
    servomotor->setLimit(-0.3, 0.3);
    addServomotor(servomotor);
    }

    // Trunk - Clavicle /////////
    {
    Servomotor * servomotor = new Servomotor("trunk-left_clavicle",
                                             *getPart("trunk"),
                                             *getPart("left_clavicle"),
                                             trunkToLeftClaviclePivot,
                                             leftClavicleToTrunkPivot,
                                             zAxis,
                                             zAxis);
    servomotor->setLimit(0., 0.);
    addServomotor(servomotor);
    }

    {
    Servomotor * servomotor = new Servomotor("trunk-right_clavicle",
                                             *getPart("trunk"),
                                             *getPart("right_clavicle"),
                                             trunkToRightClaviclePivot,
                                             rightClavicleToTrunkPivot,
                                             zAxis,
                                             zAxis);
    servomotor->setLimit(0., 0.);
    addServomotor(servomotor);
    }

    // Clavicle - Shoulder///////
    {
    Servomotor * servomotor = new Servomotor("left_clavicle-shoulder",
                                             *getPart("left_clavicle"),
                                             *getPart("left_shoulder"),
                                             leftClavicleToShoulderPivot,
                                             leftShoulderToClaviclePivot,
                                             yAxis,
                                             yAxis);
    servomotor->setLimit(-0.1, 0.1);
    addServomotor(servomotor);
    }

    {
    Servomotor * servomotor = new Servomotor("right_clavicle-shoulder",
                                             *getPart("right_clavicle"),
                                             *getPart("right_shoulder"),
                                             rightClavicleToShoulderPivot,
                                             rightShoulderToClaviclePivot,
                                             yAxis,
                                             yAxis);
    servomotor->setLimit(-0.1, 0.1);
    addServomotor(servomotor);
    }

    // Shoulder - Upper Arm /////
    {
    Servomotor * servomotor = new Servomotor("left_shoulder-upper_arm",
                                             *getPart("left_shoulder"),
                                             *getPart("left_upper_arm"),
                                             shoulderToUpperArmPivot,
                                             upperArmToShoulderPivot,
                                             xAxis,
                                             xAxis);
    servomotor->setLimit(0., 0.);
    addServomotor(servomotor);
    }

    {
    Servomotor * servomotor = new Servomotor("right_shoulder-upper_arm",
                                             *getPart("right_shoulder"),
                                             *getPart("right_upper_arm"),
                                             shoulderToUpperArmPivot,
                                             upperArmToShoulderPivot,
                                             xAxis,
                                             xAxis);
    servomotor->setLimit(0., 0.);
    addServomotor(servomotor);
    }

    // Upper Arm - Fore Arm /////
    {
    Servomotor * servomotor = new Servomotor("left_upper_arm-fore_arm",
                                             *getPart("left_upper_arm"),
                                             *getPart("left_fore_arm"),
                                             upperArmToForeArmPivot,
                                             foreArmToUpperArmPivot,
                                             yAxis,
                                             yAxis);
    servomotor->setLimit(-0.1, 0.1);
    addServomotor(servomotor);
    }

    {
    Servomotor * servomotor = new Servomotor("right_upper_arm-fore_arm",
                                             *getPart("right_upper_arm"),
                                             *getPart("right_fore_arm"),
                                             upperArmToForeArmPivot,
                                             foreArmToUpperArmPivot,
                                             yAxis,
                                             yAxis);
    servomotor->setLimit(-0.1, 0.1);
    addServomotor(servomotor);
    }

    // Fore Arm - Foot //////////
    {
    Servomotor * servomotor = new Servomotor("left_fore_arm-foot",
                                             *getPart("left_fore_arm"),
                                             *getPart("left_fore_foot"),
                                             foreArmToFootPivot,
                                             footPivot,
                                             zAxis,
                                             zAxis);
    servomotor->setLimit(0., 0.);
    addServomotor(servomotor);
    }

    {
    Servomotor * servomotor = new Servomotor("right_fore_arm-foot",
                                             *getPart("right_fore_arm"),
                                             *getPart("right_fore_foot"),
                                             foreArmToFootPivot,
                                             footPivot,
                                             zAxis,
                                             zAxis);
    servomotor->setLimit(0., 0.);
    addServomotor(servomotor);
    }

    // Trunk - Hip //////////////
    {
    Servomotor * servomotor = new Servomotor("trunk-left_hip",
                                             *getPart("trunk"),
                                             *getPart("left_hip"),
                                             trunkToLeftHipPivot,
                                             leftHipToTrunkPivot,
                                             yAxis,
                                             yAxis);
    servomotor->setLimit(-0.1, 0.1);
    addServomotor(servomotor);
    }

    {
    Servomotor * servomotor = new Servomotor("trunk-right_hip",
                                             *getPart("trunk"),
                                             *getPart("right_hip"),
                                             trunkToRightHipPivot,
                                             rightHipToTrunkPivot,
                                             yAxis,
                                             yAxis);
    servomotor->setLimit(-0.1, 0.1);
    addServomotor(servomotor);
    }

    // Hip - Thigh //////////////
    {
    Servomotor * servomotor = new Servomotor("left_hip-left_thigh",
                                             *getPart("left_hip"),
                                             *getPart("left_thigh"),
                                             hipToThighPivot,
                                             thighToHipPivot,
                                             xAxis,
                                             xAxis);
    servomotor->setLimit(0., 0.);
    addServomotor(servomotor);
    }

    {
    Servomotor * servomotor = new Servomotor("right_hip-right_thigh",
                                             *getPart("right_hip"),
                                             *getPart("right_thigh"),
                                             hipToThighPivot,
                                             thighToHipPivot,
                                             xAxis,
                                             xAxis);
    servomotor->setLimit(0., 0.);
    addServomotor(servomotor);
    }

    // Thigh - Shin /////////////
    {
    Servomotor * servomotor = new Servomotor("left_thigh-left_shin",
                                             *getPart("left_thigh"),
                                             *getPart("left_shin"),
                                             thighToShinPivot,
                                             shinToThighPivot,
                                             yAxis,
                                             yAxis);
    servomotor->setLimit(-0.1, 0.1);
    addServomotor(servomotor);
    }

    {
    Servomotor * servomotor = new Servomotor("right_thigh-right_shin",
                                             *getPart("right_thigh"),
                                             *getPart("right_shin"),
                                             thighToShinPivot,
                                             shinToThighPivot,
                                             yAxis,
                                             yAxis);
    servomotor->setLimit(-0.1, 0.1);
    addServomotor(servomotor);
    }

    // Shin - Foot //////////////
    {
    Servomotor * servomotor = new Servomotor("left_shin-foot",
                                             *getPart("left_shin"),
                                             *getPart("left_hind_foot"),
                                             shinToFootPivot,
                                             footPivot,
                                             zAxis,
                                             zAxis);
    servomotor->setLimit(0., 0.);
    addServomotor(servomotor);
    }

    {
    Servomotor * servomotor = new Servomotor("right_shin-foot",
                                             *getPart("right_shin"),
                                             *getPart("right_hind_foot"),
                                             shinToFootPivot,
                                             footPivot,
                                             zAxis,
                                             zAxis);
    servomotor->setLimit(0., 0.);
    addServomotor(servomotor);
    }

}

