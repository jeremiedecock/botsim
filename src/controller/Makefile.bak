CC = g++
CFLAGS = -I../bullet/src/ -Wall -pedantic -g -c

OBJECTS = Controller.o

.PHONY: all clean

all: $(OBJECTS)

%.o : %.cpp
	$(CC) $(CFLAGS) $<

clean:
	rm -rf $(OBJECTS)
