/* 
 * Bullet OSG Framework.
 * The sphere module.
 *
 * Copyright (c) 2015 Jérémie Decock <jd.jdhp@gmail.com>
 *
 * www.jdhp.org
 */

#ifndef BOTSIM_SPHERE_H
#define BOTSIM_SPHERE_H

#include "part.h"

#include <osg/Geode>
#include <osg/Group>
#include <osg/PositionAttitudeTransform>
#include <osg/ShapeDrawable>

#include <Eigen/Dense>

#include <btBulletDynamicsCommon.h>

namespace botsim {

    class Sphere: public botsim::Part {
        protected:
            // Bullet
            btCollisionShape * sphereShape; // TODO: rename this
            btDefaultMotionState * sphereMotionState; // TODO: rename this

            // Osg
            osg::ref_ptr<osg::Sphere> osgSphere;
            osg::ref_ptr<osg::ShapeDrawable> osgShapeDrawable;
            osg::ref_ptr<osg::Geode> osgGeode;

            // Common
            std::string name;                         // the name of this instance
            double initialRadius;                     // which unit ? mm ?
            Eigen::Vector3d initialPosition;          // which unit ? mm ?
            Eigen::Vector4d initialAngle;             // which unit ? rad ? deg ?
            Eigen::Vector3d initialInertia;           // which unit ? mm/s ?
            Eigen::Vector3d initialVelocity;          // which unit ? mm/s ?
            Eigen::Vector3d initialAngularVelocity;   // which unit ? mm/s ?

        protected:
            static int numInstances;

        public:
            Sphere(double initial_radius,
                   const Eigen::Vector3d & initial_position,
                   const Eigen::Vector4d & initial_angle,
                   const Eigen::Vector3d & initial_velocity,
                   const Eigen::Vector3d & initial_angular_velocity,
                   const Eigen::Vector3d & initial_inertia,
                   double mass,
                   double friction=0.5,
                   double rolling_friction=0.,
                   double restitution=0.,
                   const std::string & name="");

            ~Sphere();

            std::string getName() const;

        private:
            /**
             * Forbid copy of instances.
             */
            Sphere(const Sphere &);

            /**
             * Forbid assignment.
             */
            Sphere & operator = (const Sphere &);
    };

}

#endif // BOTSIM_SPHERE_H
