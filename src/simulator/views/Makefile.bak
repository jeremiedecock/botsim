CC = g++
CFLAGS = -I../../bullet/src/ -Wall -pedantic -g -c

OBJECTS = OSGView.o

.PHONY: all clean

all: $(OBJECTS)

%.o : %.cpp
	$(CC) $(CFLAGS) $<

clean:
	rm -rf $(OBJECTS)
