CC = g++
CFLAGS = -I../../../bullet_src/ -Wall -pedantic -g -c

OBJECTS = Flat.o

.PHONY: all clean

all: $(OBJECTS)

%.o : %.cpp
	$(CC) $(CFLAGS) $<

clean:
	rm -rf $(OBJECTS)
