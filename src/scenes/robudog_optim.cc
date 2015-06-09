/* 
 * Bullet OSG Framework.
 *
 * Copyright (c) 2015 Jérémie Decock <jd.jdhp@gmail.com>
 *
 * www.jdhp.org
 */

#include "bullet_environment.h"
#include "osg_environment.h"

#include "actuator.h"
#include "actuators/motor.h"

#include "builtin_parts/dynamixel_ax12.h"
#include "builtin_objects/robudog_jd.h"

#include "controller.h"
#include "controllers/constant_signal.h"
#include "controllers/sinusoidal_signal.h"
#include "controllers/robudog_controller.h"

#include "joint.h"
#include "joint_slots/hinge_slot.h"

#include "object.h"

#include "part.h"
#include "parts/ground.h"

#include "sensor.h"
#include "sensors/clock.h"

#include "tools/common_options_parser.h"
#include "tools/logger_ticks_parts_dat.h"
#include "tools/logger_ticks_parts_json.h"
#include "tools/logger_time_steps_parts_dat.h"
#include "tools/logger_time_steps_parts_json.h"
#include "tools/logger_time_steps_bullet_environment_dat.h"
#include "tools/logger_time_steps_bullet_environment_json.h"
#include "tools/tools.h"

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>
#include <set>
#include <string>

#include <Eigen/Dense>

static double ground_friction = 1.1;       // 0.5
static double ground_rolling_friction = 0.;
static double ground_restitution = 0.;

/*
 * LOCAL OPTIONS
 */

static std::string controller_parameters_file_name_opt = "";

/*
 * MAIN FUNCTION
 */

int main(int argc, char * argv[]) {

    // Parse program params ///////////////////////////////////////////////////
    
    // Declare the group of local options that are allowed on command line and config file

    /* 
     * Validates bool value
     * (see $(BOOST_ROOT)/libs/program_options/src/value_semantic.cpp):
     *
     * Any of "1", "true", "yes", "on" will be converted to "1".
     * Any of "0", "false", "no", "off" will be converted to "0".
     * Case is ignored. The 'xs' vector can either be empty, in which
     * case the value is 'true', or can contain explicit value.
     */

    po::options_description local_options_desc;
    local_options_desc.add_options()
        ("controller_filename",   po::value<std::string>(&controller_parameters_file_name_opt)->required(), "set the name of the file containing the robudog's controller parameters. Expects a filename.")
    ;

    // Parse programm options (local and common)

    botsim::CommonOptionsParser options(argc, argv, local_options_desc);

    if(options.exit) {
        return options.exitValue;
    }

    // Init Bullet ////////////////////////////////////////////////////////////

    // Robudog object ////////////////

    const Eigen::Vector3d initial_position = Eigen::Vector3d(0., 0., 0.5);
    const std::string name("robudog");
    botsim::Object * p_robudog = botsim::make_robudog_jd(initial_position, name);
    
    // Other parts ////////////////////
    
    // Ground
    botsim::Ground * p_ground = new botsim::Ground(ground_friction, ground_rolling_friction, ground_restitution);
    
    // Controllers ////////////////////
    
    botsim::Clock * p_clock_sensor = new botsim::Clock(NULL, "clock");  // TODO: UGLY WORKAROUND !
    std::set<botsim::Sensor *> sensor_set;
    sensor_set.insert(p_clock_sensor);

    Eigen::Matrix< double, 24, 1> parameters = Eigen::Matrix< double, 24, 1>::Zero();
    if(controller_parameters_file_name_opt != "") {
        std::vector<double> std_vector = botsim::text_file_to_std_vector(controller_parameters_file_name_opt);
        for(int i=0 ; i < std_vector.size() ; i++) {
            parameters(i) = std_vector[i];
        }
    } else {
        // TODO : replacer ça par l'option MENDATORY dans boost::programmoptions
        throw std::invalid_argument("The controller's parameters file is not set.");
    }
    //std::cout << "Loading controller's parameters: " << parameters << std::endl;
    botsim::RobudogController * p_robudog_controller = new botsim::RobudogController(p_robudog->getActuatorSet(), sensor_set, parameters, "robudog_controller");

    // Bullet environment /////////////
    
    // Bullet object set
    std::set<botsim::Object *> bullet_object_set;
    bullet_object_set.insert(p_robudog);

    // Bullet part set
    std::set<botsim::Part *> bullet_part_set;
    bullet_part_set.insert(p_ground);
    
    // Controller set
    std::set<botsim::Controller *> controller_set;
    controller_set.insert(p_robudog_controller);

    // Bullet environment
    botsim::BulletEnvironment * p_bullet_environment = new botsim::BulletEnvironment(bullet_object_set, bullet_part_set, controller_set, options.timeStepDurationSec, options.tickDurationSec, options.maxTicksPerTimeStep, options.simulationDurationSec);
    
    p_clock_sensor->bulletEnvironment = p_bullet_environment;  // TODO: UGLY WORKAROUND !

    ///////////////////////////////////////////////////////////////////////////

    botsim::Part * p_trunk = NULL;

    std::set<botsim::Part *>::iterator part_it;

    //std::cout << p_robudog->getPartSet().size() << std::endl;
    for(part_it = p_robudog->getPartSet().begin() ; part_it != p_robudog->getPartSet().end() ; part_it++) {
        //std::cout << "- " << (*part_it)->getName() << std::endl;
        if((*part_it)->getName() == "trunk") {
            std::cout << "OKKKKKKKKKKK" << std::endl;
            p_trunk = *part_it;
        }
    }

    Eigen::Vector3d initial_robudog_trunk_position = p_trunk->getPosition();

    // Run the simulation /////////////////////////////////////////////////////

    botsim::OSGEnvironment * p_osg_environment = NULL;

    if(options.useHeadLessMode) {
        // Run Bullet
        p_bullet_environment->run();
    } else {
        // Init OSG
        p_osg_environment = new botsim::OSGEnvironment(p_bullet_environment, options.useFullScreenMode);

        // Run OSG
        p_osg_environment->run();
    }
    
    ///////////////////////////////////////////////////////////////////////////

    Eigen::Vector3d final_robudog_trunk_position = p_trunk->getPosition();
    Eigen::Vector3d delta = final_robudog_trunk_position - initial_robudog_trunk_position;
    double score = delta.norm();

    std::cout << "Initial position: " << initial_robudog_trunk_position << std::endl;
    std::cout << "Final position: " << final_robudog_trunk_position << std::endl;
    std::cout << "Delta: " << delta << std::endl;
    std::cout << "Score: " << score << std::endl;

    // TODO: write the score in the output file

    // Clean Bullet ///////////////////////////////////////////////////////////

    delete p_bullet_environment;

    //delete p_ground;
    delete p_clock_sensor;
    delete p_robudog_controller;

    if(!options.useHeadLessMode) {
        delete p_osg_environment;
    }

    return 0;
}
