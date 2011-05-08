bin_PROGRAMS = botsim
botsim_SOURCES = ./main.cpp \
                 ./agents/Controller.h \
                 ./agents/Controller.cpp \
                 ./simulator/views/OSGView.h \
                 ./simulator/views/OSGView.cpp \
                 ./simulator/robots/Bot1.h \
                 ./simulator/robots/Bot1.cpp \
                 ./simulator/robots/Bot2.h \
                 ./simulator/robots/Bot2.cpp \
                 ./simulator/robots/Robudog.h \
                 ./simulator/robots/Robudog.cpp \
                 ./simulator/environments/FlatEnvironment.h \
                 ./simulator/environments/FlatEnvironment.cpp \
                 ./simulator/Environment.cpp \
                 ./simulator/Environment.h \
                 ./simulator/EnvironmentObject.cpp \
                 ./simulator/EnvironmentObject.h \
                 ./simulator/RobotPart.cpp \
                 ./simulator/RobotPart.h \
                 ./simulator/Servomotor.cpp \
                 ./simulator/Servomotor.h \
                 ./simulator/View.h \
                 ./simulator/View.cpp \
                 ./simulator/Robot.h \
                 ./simulator/Robot.cpp \
                 ./simulator/World.cpp
                 ./simulator/World.h \
botsim_CPPFLAGS = @LIBBULLET_CFLAGS@ @LIBOSG_CFLAGS@
botsim_LDFLAGS  = @LIBBULLET_LIBS@ @LIBOSG_LIBS@
