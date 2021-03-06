/* 
 * Bullet OSG Framework.
 *
 * Copyright (c) 2015 Jérémie Decock <jd.jdhp@gmail.com>
 *
 * www.jdhp.org
 */

#include "bullet_environment.h"
#include "osg_environment.h"

#include "controller.h"

#include "actuator.h"

#include "joints/point_to_point.h"
#include "joint_slots/point_to_point_slot.h"

#include "object.h"

#include "part.h"
#include "parts/sphere.h"
#include "parts/ground.h"

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


/*
 * LOCAL OPTIONS
 */

static double radius = 1.;
static double mass = 1.;
static double friction = 0.5;
static double rolling_friction = 0.;
static double restitution = 0.;

static Eigen::Vector3d initial_position;
static Eigen::Vector4d initial_angle;
static Eigen::Vector3d initial_velocity;
static Eigen::Vector3d initial_angular_velocity;
static Eigen::Vector3d initial_inertia;

static std::string initial_position_str_opt         = "0.,0.,10.";
static std::string initial_angle_str_opt            = "0.,0.,0.,1.";
static std::string initial_velocity_str_opt         = "1.,0.,0.";
static std::string initial_angular_velocity_str_opt = "0.,0.,0.";
static std::string initial_inertia_str_opt          = "0.,0.,0.";

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
        ("mass",             po::value<double>(&mass)->default_value(mass), "set the sphere mass (in kilograms). Expects a decimal number.")
        ("friction",         po::value<double>(&friction)->default_value(friction), "set the sphere and the ground friction value. Expects a decimal number (ideally between 0. and 1.). Best simulation results when friction is non-zero.")
        ("rolling_friction", po::value<double>(&rolling_friction)->default_value(rolling_friction), "set the sphere rolling friction value. Expects a decimal number (ideally between 0. and 1.).")
        ("restitution",      po::value<double>(&restitution)->default_value(restitution), "set the sphere and the ground restitution value. Expects a decimal number (ideally between 0. and 1.). Best simulation results using zero restitution.")
        ("radius",           po::value<double>(&radius)->default_value(radius), "set the sphere radius (in meters). Expects a decimal number.")
        ("position",         po::value<std::string>(&initial_position_str_opt)->default_value(initial_position_str_opt), "set the initial position vector of the sphere (in meters). Expects a vector of 3 decimal numbers separated with a comma and without space character (e.g. \"1.0,2.0,3.0\").")
        ("angle",            po::value<std::string>(&initial_angle_str_opt)->default_value(initial_angle_str_opt), "set the initial angle of the sphere using a quaternion representation. Expects a vector of 4 decimal numbers separated with a comma and without space character (e.g. \"1.0,2.0,3.0,4.0\").")
        ("velocity",         po::value<std::string>(&initial_velocity_str_opt)->default_value(initial_velocity_str_opt), "set the initial velocity vector of the sphere. Expects a vector of 3 decimal numbers separated with a comma and without space character (e.g. \"1.0,2.0,3.0\").")
        ("angular_velocity", po::value<std::string>(&initial_angular_velocity_str_opt)->default_value(initial_angular_velocity_str_opt), "set the initial angular velocity vector of the sphere. Expects a vector of 3 decimal numbers separated with a comma and without space character (e.g. \"1.0,2.0,3.0\").")
        ("inertia",          po::value<std::string>(&initial_inertia_str_opt)->default_value(initial_inertia_str_opt), "set the initial inertia vector of the sphere. Expects a vector of 3 decimal numbers separated with a comma and without space character (e.g. \"1.0,2.0,3.0\").")
    ;

    // Parse programm options (local and common)
    
    botsim::CommonOptionsParser options(argc, argv, local_options_desc);

    if(options.exit) {
        return options.exitValue;
    }

    // Assign some options value (vectors)
    
    initial_position = botsim::string_to_eigen_vector3(initial_position_str_opt);
    initial_angle = botsim::string_to_eigen_vector4(initial_angle_str_opt);
    initial_velocity = botsim::string_to_eigen_vector3(initial_velocity_str_opt);
    initial_angular_velocity = botsim::string_to_eigen_vector3(initial_angular_velocity_str_opt);
    initial_inertia = botsim::string_to_eigen_vector3(initial_inertia_str_opt);

    // Print options value

    if(options.verbose) {
        std::cout << "MASS: " << mass << "kg" << std::endl;
        std::cout << "FRICTION: " << friction << std::endl;
        std::cout << "ROLLING FRICTION: " << rolling_friction << std::endl;
        std::cout << "RESTITUTION: " << restitution << std::endl;
        std::cout << "RADIUS: " << radius << "m" << std::endl;
        std::cout << "INITIAL POSITION: " << botsim::eigen_vector_to_string(initial_position) << std::endl;
        std::cout << "INITIAL ANGLE: " << botsim::eigen_vector_to_string(initial_angle) << std::endl;
        std::cout << "INITIAL VELOCITY: " << botsim::eigen_vector_to_string(initial_velocity) << std::endl;
        std::cout << "INITIAL ANGULAR VELOCITY: " << botsim::eigen_vector_to_string(initial_angular_velocity) << std::endl;
        std::cout << "INITIAL INERTIA: " << botsim::eigen_vector_to_string(initial_inertia) << std::endl;
    }

    // Init Bullet ////////////////////////////////////////////////////////////

    // Pendulum object ////////////////

    // Pendulum parts
    botsim::Sphere * p_sphere = new botsim::Sphere(radius, initial_position, initial_angle, initial_velocity, initial_angular_velocity, initial_inertia, mass, friction, rolling_friction, restitution, "pendulum_sphere");

    std::set<botsim::Part *> pendulum_part_set;
    pendulum_part_set.insert(p_sphere);

    // Pendulum joints
    Eigen::Vector3d pendulum_p2p_pivot(-5., 0., 0.);
    botsim::PointToPointSlot * p_pendulum_p2p_slot = new botsim::PointToPointSlot(pendulum_p2p_pivot);
    botsim::PointToPoint * p_pendulum_p2p = new botsim::PointToPoint(p_sphere, p_pendulum_p2p_slot, "pendulum_point_to_point");

    std::set<botsim::Joint *> pendulum_joint_set;
    pendulum_joint_set.insert(p_pendulum_p2p);
    
    // Pendulum actuators
    std::set<botsim::Actuator *> pendulum_actuator_set;

    // Pendulum object
    botsim::Object * p_pendulum = new botsim::Object(pendulum_part_set, pendulum_joint_set, pendulum_actuator_set, "pendulum");

    // Other parts ////////////////////
    
    // Ground
    botsim::Ground * p_ground = new botsim::Ground(friction, rolling_friction, restitution);

    // Bullet environment /////////////
    
    // Bullet object set
    std::set<botsim::Object *> bullet_object_set;
    bullet_object_set.insert(p_pendulum);

    // Bullet part set
    std::set<botsim::Part *> bullet_part_set;
    bullet_part_set.insert(p_ground);
    
    // Controller set
    std::set<botsim::Controller *> controller_set;

    // Bullet environment
    botsim::BulletEnvironment * p_bullet_environment = new botsim::BulletEnvironment(bullet_object_set, bullet_part_set, controller_set, options.timeStepDurationSec, options.tickDurationSec, options.maxTicksPerTimeStep, options.simulationDurationSec);

    // Init log ///////////////////////////////////////////////////////////////

    // Bullet time steps dat log
    botsim::LoggerTimeStepsBulletEnvironmentDat * p_logger_time_steps_bullet_environment_dat = new botsim::LoggerTimeStepsBulletEnvironmentDat();
    p_bullet_environment->attachTimeStepObserver(p_logger_time_steps_bullet_environment_dat);

    // Bullet time steps json log
    botsim::LoggerTimeStepsBulletEnvironmentJson * p_logger_time_steps_bullet_environment_json = new botsim::LoggerTimeStepsBulletEnvironmentJson();
    p_bullet_environment->attachTimeStepObserver(p_logger_time_steps_bullet_environment_json);

    // Parts time steps dat log
    botsim::LoggerTimeStepsPartsDat * p_logger_time_steps_parts_dat = new botsim::LoggerTimeStepsPartsDat(bullet_part_set);
    p_bullet_environment->attachTimeStepObserver(p_logger_time_steps_parts_dat);

    // Parts time steps json log
    botsim::LoggerTimeStepsPartsJson * p_logger_time_steps_parts_json = new botsim::LoggerTimeStepsPartsJson(bullet_part_set);
    p_bullet_environment->attachTimeStepObserver(p_logger_time_steps_parts_json);

    // Parts ticks dat log
    botsim::LoggerTicksPartsDat * p_logger_ticks_parts_dat = new botsim::LoggerTicksPartsDat(bullet_part_set);
    p_bullet_environment->attachTickObserver(p_logger_ticks_parts_dat);

    // Parts ticks json log
    botsim::LoggerTicksPartsJson * p_logger_ticks_parts_json = new botsim::LoggerTicksPartsJson(bullet_part_set);
    p_bullet_environment->attachTickObserver(p_logger_ticks_parts_json);


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

    // Clean Bullet ///////////////////////////////////////////////////////////

    delete p_logger_time_steps_bullet_environment_dat;
    delete p_logger_time_steps_bullet_environment_json;
    delete p_logger_time_steps_parts_dat;
    delete p_logger_time_steps_parts_json;
    delete p_logger_ticks_parts_dat;
    delete p_logger_ticks_parts_json;

    std::cout << "Delete Bullet environment." << std::endl;
    delete p_bullet_environment;

    //delete p_sphere;
    delete p_pendulum_p2p_slot;
    delete p_pendulum_p2p;
    delete p_pendulum;
    //delete p_ground;

    if(!options.useHeadLessMode) {
        std::cout << "Delete OSG environment." << std::endl;
        delete p_osg_environment;
    }

    std::cout << "Bye." << std::endl;

    return 0;
}
