CC = g++
CFLAGS = -I../bullet/src/ -Wall -pedantic -g -c

SUBDIR = environments robots views

OBJECTS = World.o Robot.o RobotPart.o Environment.o EnvironmentObject.o Servomotor.o View.o

.PHONY: all $(SUBDIR) clean

all: $(OBJECTS) $(SUBDIR)

%.o : %.cpp
	$(CC) $(CFLAGS) $<

$(SUBDIR):
	$(MAKE) --directory=$@

clean:
	rm -rf $(OBJECTS)
	$(MAKE) clean --directory=robots
	$(MAKE) clean --directory=environments
	$(MAKE) clean --directory=views

