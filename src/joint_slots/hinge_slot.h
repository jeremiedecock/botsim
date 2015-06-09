/* 
 * Bullet OSG Framework.
 * The hinge slot module.
 *
 * Copyright (c) 2015 Jérémie Decock <jd.jdhp@gmail.com>
 *
 * www.jdhp.org
 */

#ifndef BOTSIM_HINGE_SLOT_H
#define BOTSIM_HINGE_SLOT_H

#include "joint_slot.h"

#include <Eigen/Dense>

namespace botsim {

    class HingeSlot: public botsim::JointSlot {

        protected:
            Eigen::Vector3d pivot;
            Eigen::Vector3d axis;

        public:
            HingeSlot(const Eigen::Vector3d & pivot,
                      const Eigen::Vector3d & axis);

            virtual ~HingeSlot();

            Eigen::Vector3d getPivot() const;

            Eigen::Vector3d getAxis() const;

        private:
            /**
             * Forbid copy of instances.
             */
            HingeSlot(const HingeSlot &);

            /**
             * Forbid assignment.
             */
            HingeSlot & operator = (const HingeSlot &);
    };

}

#endif // BOTSIM_HINGE_SLOT_H
