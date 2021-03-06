/* 
 * Bullet OSG Framework.
 * Bullet environment logger module.
 *
 * Copyright (c) 2015 Jérémie Decock <jd.jdhp@gmail.com>
 *
 * www.jdhp.org
 */

#ifndef BOTSIM_LOGGER_TIME_STEPS_BULLET_ENVIRONMENT_JSON_H
#define BOTSIM_LOGGER_TIME_STEPS_BULLET_ENVIRONMENT_JSON_H

#include "bullet_environment.h"

#include <fstream>
#include <map>
#include <string>
#include <vector>

namespace botsim {

    class LoggerTimeStepsBulletEnvironmentJson : public TimeStepObserver {
        private:
            std::string filepath;
            std::ofstream * ofs;

            std::map<std::string, std::vector<double> > dataMap;

        public:
            LoggerTimeStepsBulletEnvironmentJson(std::string filepath="");

            ~LoggerTimeStepsBulletEnvironmentJson();

            void update(BulletEnvironment * bullet_environment);

            std::string getFilepath() const;

        private:
            /**
             * Forbid copy of instances.
             */
            LoggerTimeStepsBulletEnvironmentJson(const LoggerTimeStepsBulletEnvironmentJson &);

            /**
             * Forbid assignment.
             */
            LoggerTimeStepsBulletEnvironmentJson & operator = (const LoggerTimeStepsBulletEnvironmentJson &);
    };
}

#endif // BOTSIM_LOGGER_TIME_STEPS_BULLET_ENVIRONMENT_JSON_H
