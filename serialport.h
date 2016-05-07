#ifndef SERIALPORT_H_INCLUDED
#define SERIALPORT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>


static struct termios oldtty;
int set_interface_attribs (int fd, int speed, int parity,int stop=1);
int set_blocking (int fd, int should_block);


#endif // SERIALPORT_H_INCLUDED
