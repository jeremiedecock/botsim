/* 
 * Bullet OSG Framework.
 * The sinusoidal signal module.
 *
 * Copyright (c) 2015 Jérémie Decock <jd.jdhp@gmail.com>
 *
 * www.jdhp.org
 */

#ifndef BOTSIM_SINUSOIDAL_SIGNAL_CONTROLLER_H
#define BOTSIM_SINUSOIDAL_SIGNAL_CONTROLLER_H

#include "controller.h"

namespace botsim {

    class SinusoidalSignal: public botsim::Controller {
        protected:
            // Common
            double amplitude;  // The peak deviation of the function from zero.
            double frequency;  // The number of oscillations (cycles) that occur each second of time.
            double phase;      // Specifies (in radians) where in its cycle the oscillation is at t = 0.
            std::string name;  // The name of this instance.

        public:
            /**
             * A very basic controler wich sends a sinusoidal signal to actuators.
             * It only requires a Clock (time) sensor.
             * The signal "y" sent to actuators with respect to time is:
             *
             * y(t) = amplitude * sin(2.0 * PI * frequency * t + phase)
             *
             * \param[in] amplitude  The peak deviation of the function from zero.
             * \param[in] frequency  The number of oscillations (cycles) that occur each second of time.
             * \param[in] phase      Specifies (in radians) where in its cycle the oscillation is at t = 0.
             * \param[in] name       The name of this instance.
             */
            SinusoidalSignal(const std::set<botsim::Actuator *> & actuator_set,
                             const std::set<botsim::Sensor *> & sensor_set,
                             double _amplitude,
                             double _frequency,
                             double _phase,
                             const std::string & _name="");

            ~SinusoidalSignal();

            double computeSignalValue(double time) const;

            void updateActuators();

            double getAmplitude() const;

            double getFrequency() const;

            double getPhase() const;

            std::string getName() const;

        private:
            /**
             * Forbid copy of instances.
             */
            SinusoidalSignal(const SinusoidalSignal &);

            /**
             * Forbid assignment.
             */
            SinusoidalSignal & operator = (const SinusoidalSignal &);
    };

}

#endif // BOTSIM_SINUSOIDAL_SIGNAL_CONTROLLER_H
