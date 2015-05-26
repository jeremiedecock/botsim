# Copyright (c) 2015 Jérémie DECOCK

# Define the config_and_add_executable macro
macro(config_and_add_executable EXEC_NAME SRC_FILE)
    # Add executable
    add_executable(${EXEC_NAME} ${SRC_FILE})

    # Link to the internal libraries
    target_link_libraries(${EXEC_NAME} core parts tools)

    # Link to Bullet
    target_link_libraries(${EXEC_NAME} ${BULLET_LIBRARIES})

    # Link to OSG
    target_link_libraries(${EXEC_NAME} ${OPENSCENEGRAPH_LIBRARIES})
endmacro()

# EXECUTABLES #######################################################

# Set options
option(BUILD_DEMO "Build the default demo (falling cubes)" ON)
option(BUILD_CUBES_1 "Build cubes 1 (4 falling cubes with various sizes and weights)" OFF)

# Set executables
if(BUILD_DEMO)
    config_and_add_executable(demo demo.cc)
endif(BUILD_DEMO)

if(BUILD_CUBES_1)
    config_and_add_executable(cubes_1 cubes_1.cc)
endif(BUILD_CUBES_1)
