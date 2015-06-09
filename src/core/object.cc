/* 
 * Bullet OSG Framework.
 * Object module.
 *
 * Copyright (c) 2015 Jérémie Decock <jd.jdhp@gmail.com>
 *
 * www.jdhp.org
 */

#include "object.h"

botsim::Object::Object(const std::set<botsim::Part *> & part_set,
                       const std::set<botsim::Joint *> & joint_set,
                       const std::set<botsim::Actuator *> & actuator_set,
                       const std::string & _name) :
                           partSet(part_set),
                           jointSet(joint_set),
                           actuatorSet(actuator_set),
                           name(_name) { }

std::set<botsim::Part *> botsim::Object::getPartSet() const {
    return this->partSet;
}

std::set<botsim::Joint *> botsim::Object::getJointSet() const {
    return this->jointSet;
}

std::set<botsim::Actuator *> botsim::Object::getActuatorSet() const {
    return this->actuatorSet;
}

std::string botsim::Object::getName() const {
    return this->name;
}
