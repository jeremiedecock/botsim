/* 
 * Bullet OSG Framework.
 * Bullet environment logger module.
 *
 * Copyright (c) 2015 Jérémie Decock <jd.jdhp@gmail.com>
 *
 * www.jdhp.org
 */

#include "logger_time_steps_bullet_environment_dat.h"
#include "tools/tools.h"

#include <iostream>

const std::string DEFAULT_FILE_PATH = "time_steps_bullet_environment.dat"; // TODO ?

simulator::LoggerTimeStepsBulletEnvironmentDat::LoggerTimeStepsBulletEnvironmentDat(std::string filepath) {
    // Set filepath
    if(filepath == "") {
        this->filepath = DEFAULT_FILE_PATH;
    } else {
        this->filepath = filepath;
    }
    
    // Open the log file
    std::cout << "Open " << this->filepath << std::endl;
    this->ofs = new std::ofstream(this->filepath.c_str());
    
    // Write the header
    (* this->ofs) << "#elapsed_simulation_time_sec  ";
    (* this->ofs) << "elapsed_user_time_sec  ";
    //(* this->ofs) << "time_step_sec  ";
    (* this->ofs) << "fixed_sub_time_step_sec  ";
    //(* this->ofs) << "num_sub_steps  ";
    (* this->ofs) << "max_sub_steps  ";
    (* this->ofs) << std::endl;
}

simulator::LoggerTimeStepsBulletEnvironmentDat::~LoggerTimeStepsBulletEnvironmentDat() {
    // Open the log file
    std::cout << "Close " << this->filepath << std::endl;
    this->ofs->flush();
    this->ofs->close();

    // Destroy dynamic objects
    delete this->ofs;
}

void simulator::LoggerTimeStepsBulletEnvironmentDat::update(BulletEnvironment * bullet_environment) {
    double elapsed_simulation_time_sec = bullet_environment->getElapsedSimulationTimeSec();
    double elapsed_user_time_sec = bullet_environment->getElapsedUserTimeSec();
    //double time_step_sec = bullet_environment->();
    double fixed_sub_time_step_sec = bullet_environment->getBulletFixedTimeSubStepSec();
    //double num_sub_steps = time_step_sec / fixed_sub_time_step_sec;
    double max_sub_steps = bullet_environment->getBulletMaxSubSteps();
    
    (* this->ofs) << elapsed_simulation_time_sec << " ";
    (* this->ofs) << elapsed_user_time_sec << " ";
    //(* this->ofs) << time_step_sec << " ";
    (* this->ofs) << fixed_sub_time_step_sec << " ";
    //(* this->ofs) << num_sub_steps << " ";
    (* this->ofs) << max_sub_steps << " ";
    (* this->ofs) << std::endl;
}

std::string simulator::LoggerTimeStepsBulletEnvironmentDat::getFilepath() const {
    return this->filepath;
}
