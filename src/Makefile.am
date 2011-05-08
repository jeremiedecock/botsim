bin_PROGRAMS = botsim
botsim_SOURCES = ./main.cpp \
                 ./agents/Controller.h \
                 ./agents/Controller.cpp \
                 ./simulator/Environment.h \
                 ./simulator/World.h \
                 ./simulator/RobotPart.h \
                 ./simulator/views/OSGView.h \
                 ./simulator/views/OSGView.cpp \
                 ./simulator/Servomotor.cpp \
                 ./simulator/robots/Bot1.h \
                 ./simulator/robots/Bot2.h \
                 ./simulator/robots/Robudog.h \
                 ./simulator/robots/Bot1.cpp \
                 ./simulator/robots/Bot2.cpp \
                 ./simulator/robots/Robudog.cpp \
                 ./simulator/Robot.cpp \
                 ./simulator/View.h \
                 ./simulator/Environment.cpp \
                 ./simulator/RobotPart.cpp \
                 ./simulator/EnvironmentObject.h \
                 ./simulator/Servomotor.h \
                 ./simulator/environments/FlatEnvironment.cpp \
                 ./simulator/environments/FlatEnvironment.h \
                 ./simulator/EnvironmentObject.cpp \
                 ./simulator/View.cpp \
                 ./simulator/Robot.h \
                 ./simulator/World.cpp
botsim_CPPFLAGS = @LIBBULLET_CFLAGS@ @LIBOSG_CFLAGS@
botsim_LDFLAGS  = @LIBBULLET_LIBS@ @LIBOSG_LIBS@
