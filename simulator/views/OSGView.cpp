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

#include "Views.h"

#ifndef VECTOR_HEADER
    #define VECTOR_HEADER
    #include <vector>
#endif

#ifndef BULLET_HEADERS
    #define BULLET_HEADERS
    #include <btBulletDynamicsCommon.h>
#endif

#include <iostream>

#include <pthread.h>

#include <osg/Group>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osgViewer/Viewer>

// NodeData /////////////////////////////////////////////////////////////////////////////////////////

class NodeData : public osg::Referenced {
        private:
                RobotPart * robotPart;

        public:
                NodeData(RobotPart * b) {
                        robotPart = b;
                }

                RobotPart * getRobotPart() {
                        return robotPart;
                }
};

// NodeUpdateCallback ///////////////////////////////////////////////////////////////////////////////

class NodeUpdateCallback : public osg::NodeCallback {
        public:
                virtual void operator() (osg::Node * node, osg::NodeVisitor * nv) {
                        osg::PositionAttitudeTransform * pat = dynamic_cast < osg::PositionAttitudeTransform * >(node);

                        NodeData * data = dynamic_cast < NodeData * >(pat->getUserData());

                        // TODO : try with getCenterOfMassPosition ()
                        btTransform bulletTransform;
                        bulletTransform = data->getRobotPart()->getWorldTransform();

                        pat->setPosition(osg::Vec3(bulletTransform.getOrigin().getX(),
                                                   bulletTransform.getOrigin().getY(),
                                                   bulletTransform.getOrigin().getZ()));
                        pat->setAttitude(osg::Quat(bulletTransform.getRotation().x(),
                                                   bulletTransform.getRotation().y(),
                                                   bulletTransform.getRotation().z(),
                                                   bulletTransform.getRotation().w()));

                        traverse(node, nv);
                }
};

// OSGView //////////////////////////////////////////////////////////////////////////////////////////

OSGView::OSGView() {

}

void OSGView::run() {
    if(world != NULL) {  // TODO : faire qqch de + propre ici
        pthread_create(&tid, NULL, &OSGView::fn_thread, world);
    }
}

void OSGView::close() {
    // TODO : Termine le thread désigné par tid
}

void * OSGView::fn_thread(void * args) {
    World * world = static_cast< World * >(args);

    std::vector<RobotPart *> robotParts = world->getRobot()->getParts();
    std::vector<RobotPart *>::iterator it;

    // Init OSG /////////////////////////////////////////////////////

    // Make the scene graph /////

    // Root
    osg::Group * root = new osg::Group();

    // Ground
    osg::Box * ground = new osg::Box(osg::Vec3(0, 0, -0.5), 1.0f);
    ground->setHalfLengths(osg::Vec3(500, 500, 0.5));

    osg::ShapeDrawable * groundSd = new osg::ShapeDrawable(ground);

    osg::Geode * groundGeode = new osg::Geode();
    groundGeode->addDrawable(groundSd);

    root->addChild(groundGeode);

    // RobotParts
    for(it = robotParts.begin() ; it != robotParts.end() ; it++) {
        RobotPart * robotPart = *it;
        btCollisionShape * bulletShape = robotPart->getCollisionShape();
        int bulletShapeType = bulletShape->getShapeType();

        osg::Shape * osgShape = NULL;

        if(bulletShapeType == BOX_SHAPE_PROXYTYPE) {

            btVector3 extents = dynamic_cast < btBoxShape * >(bulletShape)->getHalfExtentsWithMargin();
            osgShape = new osg::Box(osg::Vec3(0, 0, 0), 1.0f);
            dynamic_cast < osg::Box * >(osgShape)->setHalfLengths(osg::Vec3(extents.getX(), extents.getY(), extents.getZ()));

        } else if(bulletShapeType == SPHERE_SHAPE_PROXYTYPE) {

            btScalar radius = dynamic_cast < btSphereShape * >(bulletShape)->getRadius();
            osgShape = new osg::Sphere(osg::Vec3(0, 0, 0), radius);

        } else if(bulletShapeType == CAPSULE_SHAPE_PROXYTYPE) {

            btScalar radius = dynamic_cast < btCapsuleShape * >(bulletShape)->getRadius();
            btScalar halfHeight = dynamic_cast < btCapsuleShape * >(bulletShape)->getHalfHeight();
            float height = halfHeight * 2 - radius * 4 ; // TODO ????????????????????????????????
            osgShape = new osg::Capsule( osg::Vec3(0,0,0), radius, height );

            std::cout << (*it)->getName() << " : btHalfHeight = " << halfHeight << ", osgHeight = " << height <<  ", btRadius = " << radius << std::endl;

        } else if(bulletShapeType == CONE_SHAPE_PROXYTYPE) {

            // TODO
            osgShape = new osg::Cone( osg::Vec3(0,0,0), 1.0f, 3.0f );

        } else if(bulletShapeType == CYLINDER_SHAPE_PROXYTYPE) {

            // TODO
            osgShape = new osg::Cylinder( osg::Vec3(0,0,0), 1.0f, 3.0f );

        } else {

            std::cout << "Error : unknown " << (*it)->getName() << "'s shape" << std::endl;

        }

        if(osgShape != NULL) {
            osg::ShapeDrawable * robotPartSd = new osg::ShapeDrawable(osgShape);

            osg::Geode * robotPartNode = new osg::Geode();
            robotPartNode->addDrawable(robotPartSd);

            osg::PositionAttitudeTransform * pat = new osg::PositionAttitudeTransform();
            pat->addChild(robotPartNode);
            pat->setUserData(new NodeData(*it));
            pat->setUpdateCallback(new NodeUpdateCallback());
            root->addChild(pat);
        }
    }

    // Make the viewer /////
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
    viewer->setUpViewInWindow( 32, 32, 512, 512 );
    viewer->setSceneData(root);
    viewer->run();

    return 0;
}

