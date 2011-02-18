bin_PROGRAMS = botsim
botsim_SOURCES = ./main.cpp \
                 ./agents/Controller.cpp \
                 ./simulator/views/OSGView.cpp \
                 ./simulator/Servomotor.cpp \
                 ./simulator/robots/Bot1.cpp \
                 ./simulator/robots/Bot2.cpp \
                 ./simulator/robots/Robudog.cpp \
                 ./simulator/Robot.cpp \
                 ./simulator/Environment.cpp \
                 ./simulator/RobotPart.cpp \
                 ./simulator/environments/Flat.cpp \
                 ./simulator/EnvironmentObject.cpp \
                 ./simulator/View.cpp \
                 ./simulator/World.cpp
botsim_CPPFLAGS = -I${top_srcdir}/include/bullet 
botsim_LDADD    = ${top_srcdir}/lib/libbulletdynamics.a \
                  ${top_srcdir}/lib/libbulletcollision.a \
                  ${top_srcdir}/lib/libbulletmath.a
botsim_LDFLAGS  = `pkg-config --libs openscenegraph`
