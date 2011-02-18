#include <sys/time.h>

#ifndef ROBOTS_HEADERS
    #define ROBOTS_HEADERS
    #include "../simulator/robots/Robots.h"
#endif

void moveBot1(struct timeval, Robot *);

void moveBot2(struct timeval, Robot *);

void moveRobudog(struct timeval, Robot *);

