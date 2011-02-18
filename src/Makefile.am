bin_PROGRAMS = botsim
botsim_SOURCES = ./main.cpp \
                 ./agents/Controller.h \
                 ./agents/Controller.cpp \
                 ./simulator/Environment.h \
                 ./simulator/World.h \
                 ./simulator/RobotPart.h \
                 ./simulator/views/Views.h \
                 ./simulator/views/OSGView.cpp \
                 ./simulator/Servomotor.cpp \
                 ./simulator/robots/Robots.h \
                 ./simulator/robots/Bot1.cpp \
                 ./simulator/robots/Bot2.cpp \
                 ./simulator/robots/Robudog.cpp \
                 ./simulator/Robot.cpp \
                 ./simulator/View.h \
                 ./simulator/Environment.cpp \
                 ./simulator/RobotPart.cpp \
                 ./simulator/EnvironmentObject.h \
                 ./simulator/Servomotor.h \
                 ./simulator/environments/Flat.cpp \
                 ./simulator/environments/Environments.h \
                 ./simulator/EnvironmentObject.cpp \
                 ./simulator/View.cpp \
                 ./simulator/Robot.h \
                 ./simulator/World.cpp
botsim_CPPFLAGS = @LIBBULLET_CFLAGS@ @LIBOSG_CFLAGS@
botsim_LDFLAGS  = @LIBBULLET_LIBS@ @LIBOSG_LIBS@
