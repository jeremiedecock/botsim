/* 
 * Bullet OSG Framework.
 * The clock module.
 *
 * Copyright (c) 2015 Jérémie Decock <jd.jdhp@gmail.com>
 *
 * www.jdhp.org
 */

#ifndef BOTSIM_CLOCK_SENSOR_H
#define BOTSIM_CLOCK_SENSOR_H

#include "bullet_environment.h"
#include "sensor.h"

#include <Eigen/Dense>

namespace botsim {

    class Clock: public botsim::Sensor {
        protected:
            // Common
            //botsim::BulletEnvironment * bulletEnvironment;

            std::string name;                         // the name of this instance

            double simulationDurationSec;

        public:
            botsim::BulletEnvironment * bulletEnvironment;  // TODO: UGLY WORKAROUND !

        public:
            Clock(botsim::BulletEnvironment * bullet_environment,
                  const std::string & _name="");

            ~Clock();

            Eigen::VectorXd getPercepts();

            std::string getName() const;

            double getSimulationDurationSec() const;

        private:
            /**
             * Forbid copy of instances.
             */
            Clock(const Clock &);

            /**
             * Forbid assignment.
             */
            Clock & operator = (const Clock &);
    };

}

#endif // BOTSIM_CLOCK_SENSOR_H
