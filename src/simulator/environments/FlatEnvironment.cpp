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

#include "FlatEnvironment.h"

FlatEnvironment::FlatEnvironment() {
    btCollisionShape * collisionShape = new btStaticPlaneShape(btVector3(0, 0, 1), 0);

    EnvironmentObject::btRigidBodyConstructionInfo rigidBodyCI(0,
                                                               NULL,
                                                               collisionShape,
                                                               btVector3(0, 0, 0));

    body = new EnvironmentObject(rigidBodyCI);

    body->setCenterOfMassTransform(btTransform(btQuaternion(0,0,0,1),
                                   btVector3(0.0f, 0.0f, 0.0f)));
}

FlatEnvironment::~FlatEnvironment() {
    // TODO : delete
}
