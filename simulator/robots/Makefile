CC = g++
CFLAGS = -I../../../bullet_src/ -Wall -pedantic -g -c

OBJECTS = Bot1.o Bot2.o Robudog.o

.PHONY: all clean

all: $(OBJECTS)

%.o : %.cpp
	$(CC) $(CFLAGS) $<

clean:
	rm -rf $(OBJECTS)
