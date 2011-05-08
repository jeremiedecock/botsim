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
#include <iostream>
#include <vector>

#include <pthread.h>

#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/PositionAttitudeTransform>
#include <osgViewer/Viewer>

#ifdef SHADOW
#include <osgShadow/ShadowedScene>
#include <osgShadow/ShadowMap>
#include <osg/LightSource>
#endif

#include "Views.h"

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

OSGView::~OSGView() {
    // TODO : delete
}

void OSGView::run() {
    if(world != NULL) {  // TODO : faire qqch de + propre ici
        pthread_create(&tid, NULL, &OSGView::fn_thread, world);
    }
}

void OSGView::close() {
    // TODO : Termine le thread désigné par tid
}

static osg::ref_ptr<osg::Node> createBase(const osg::Vec3&, float);

void * OSGView::fn_thread(void * args) {
    World * world = static_cast< World * >(args);

    std::vector<RobotPart *> robotParts = world->getRobot()->getParts();
    std::vector<RobotPart *>::iterator it;

    // Init OSG /////////////////////////////////////////////////////

    // Make the scene graph /////

    // Root
    osg::ref_ptr<osg::Group> root = new osg::Group();

    // Ground
    //osg::ref_ptr<osg::Box> ground = new osg::Box(osg::Vec3(0, 0, -0.5), 1.0f);
    //ground->setHalfLengths(osg::Vec3(500, 500, 0.5));

    //osg::ref_ptr<osg::ShapeDrawable> groundSd = new osg::ShapeDrawable(ground);

    //osg::ref_ptr<osg::Geode> groundGeode = new osg::Geode();
    //groundGeode->addDrawable(groundSd);
    //root->addChild(groundGeode);

    osg::ref_ptr<osg::Node> ground = createBase(osg::Vec3(0, 0, -0.5), 1000.0f);
    root->addChild(ground);

#ifdef SHADOW
    osg::ref_ptr<osg::Geode> lightMarkerGeode = new osg::Geode();

    // SHADOW
    osg::ref_ptr<osgShadow::ShadowedScene> shadowedScene = new osgShadow::ShadowedScene();
    osg::ref_ptr<osgShadow::ShadowMap> sm = new osgShadow::ShadowMap();
    shadowedScene->setShadowTechnique(sm);

    // MAIN LIGHT SOURCE 
    osg::Vec3 lightPosition(0, 0, 3); 
    osg::ref_ptr<osg::LightSource> ls = new osg::LightSource;
    ls->getLight()->setPosition(osg::Vec4(lightPosition, 1));
    ls->getLight()->setAmbient(osg::Vec4(0.2, 0.2, 0.2, 1.0));
    ls->getLight()->setDiffuse(osg::Vec4(0.6, 0.6, 0.6, 1.0));

    shadowedScene->addChild(root);
    shadowedScene->addChild(ls);
    shadowedScene->addChild(lightMarkerGeode);

    lightMarkerGeode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(lightPosition + osg::Vec3(0,0,0.5f), 0.1f)));
#endif

    // RobotParts
    for(it = robotParts.begin() ; it != robotParts.end() ; it++) {
        RobotPart * robotPart = *it;
        btCollisionShape * bulletShape = robotPart->getCollisionShape();
        int bulletShapeType = bulletShape->getShapeType();

        // TODO : howto use osg::ref_ptr<> here ?
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
            osg::ref_ptr<osg::ShapeDrawable> robotPartSd = new osg::ShapeDrawable(osgShape);

            osg::ref_ptr<osg::Geode> robotPartNode = new osg::Geode();
            robotPartNode->addDrawable(robotPartSd);

            osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
            pat->addChild(robotPartNode);
            pat->setUserData(new NodeData(*it));
            pat->setUpdateCallback(new NodeUpdateCallback());
            root->addChild(pat);
        }
    }

    // Make the viewer /////
    osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
    viewer->setUpViewInWindow( 32, 32, 512, 512 );
#ifdef SHADOW
    viewer->setSceneData(shadowedScene);
#else
    viewer->setSceneData(root);
#endif
    viewer->run();

    return 0;
}


/**
 *
 */
static osg::ref_ptr<osg::Node> createBase(const osg::Vec3& center, float radius) {

    int numTilesX = 10;
    int numTilesY = 10;

    float width = 2 * radius;
    float height = 2 * radius;

    osg::Vec3 v000(center - osg::Vec3(width * 0.5f, height * 0.5f, 0.0f));
    osg::Vec3 dx(osg::Vec3(width/((float)numTilesX), 0.0, 0.0f));
    osg::Vec3 dy(osg::Vec3(0.0f, height/((float)numTilesY), 0.0f));

    // fill in vertices for grid, note numTilesX+1 * numTilesY+1...
    osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array;
    int iy;
    for(iy = 0 ; iy <= numTilesY ; ++iy) {
        for(int ix=0 ; ix<=numTilesX ; ++ix) {
            coords->push_back(v000 + dx*(float)ix + dy*(float)iy);
        }
    }

    //Just two colours - black and white.
    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
    colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f)); // white
    colors->push_back(osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f)); // black
    int numColors=colors->size();

    int numIndicesPerRow=numTilesX+1;
    osg::ref_ptr<osg::UByteArray> coordIndices = new osg::UByteArray; // assumes we are using less than 256 points...
    osg::ref_ptr<osg::UByteArray> colorIndices = new osg::UByteArray;
    for(iy=0 ; iy<numTilesY ; ++iy) {
        for(int ix=0 ; ix<numTilesX ; ++ix) {
            // four vertices per quad.
            coordIndices->push_back(ix    +(iy+1)*numIndicesPerRow);
            coordIndices->push_back(ix    +iy*numIndicesPerRow);
            coordIndices->push_back((ix+1)+iy*numIndicesPerRow);
            coordIndices->push_back((ix+1)+(iy+1)*numIndicesPerRow);

            // one color per quad
            colorIndices->push_back((ix+iy)%numColors);
        }
    }

    // set up a single normal
    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
    normals->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    geom->setVertexArray(coords);
    geom->setVertexIndices(coordIndices);

    geom->setColorArray(colors);
    geom->setColorIndices(colorIndices);
    geom->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE);

    geom->setNormalArray(normals);
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

    geom->addPrimitiveSet(new osg::DrawArrays(
        osg::PrimitiveSet::QUADS,
        0,
        coordIndices->size()));

    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(geom);

    return geode.get();
}
