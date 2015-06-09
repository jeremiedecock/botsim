/* 
 * Bullet OSG Framework.
 * The constant signal module.
 *
 * Copyright (c) 2015 Jérémie Decock <jd.jdhp@gmail.com>
 *
 * www.jdhp.org
 */

#ifndef BOTSIM_CONSTANT_SIGNAL_CONTROLLER_H
#define BOTSIM_CONSTANT_SIGNAL_CONTROLLER_H

#include "controller.h"

namespace botsim {

    class ConstantSignal: public botsim::Controller {
        protected:
            // Common
            double constantValue; // The value of the signal.
            std::string name;     // The name of this instance.

        public:
            ConstantSignal(const std::set<botsim::Actuator *> & actuator_set,
                           const std::set<botsim::Sensor *> & sensor_set,
                           const double & _const_value,
                           std::string _name="");

            ~ConstantSignal();

            void updateActuators();

            double getConstantValue() const;

            std::string getName() const;

        private:
            /**
             * Forbid copy of instances.
             */
            ConstantSignal(const ConstantSignal &);

            /**
             * Forbid assignment.
             */
            ConstantSignal & operator = (const ConstantSignal &);
    };

}

#endif // BOTSIM_CONSTANT_SIGNAL_CONTROLLER_H
