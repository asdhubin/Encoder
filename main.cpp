#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>

#include "odometer.h"
#include "serialport.h"

#define portname  "/dev/ttyUSB0"
#define revolution 1000 //every 1000 of encoder number is 1mm

int main()
{
    int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);

    if (fd < 0)
    {
        printf("error opening the device\n");
    }


    /*CHANGES*/
    if(set_interface_attribs(fd, B9600, 0)!=0)
    {            printf("hello");
        printf("error set interface\n");
    }

    else


    if(set_blocking(fd, 0)!=0)
    {
        printf("error set blocking\n");
    }

    else
        printf("done");

    // what is this stray end of comment?
    // suggest enabling all the compiler warings
    // and fixing the warnings
    // */
    if( set_interface_attribs (fd, B9600, 0) )
    { // then set_interface_attribs failed
        return -1;
    }

    // implied else set_interface_attribs successful

    if( set_blocking (fd, 0) )                // set no blocking
    { // then set_blocking failed
        return -1;   // might need to also restore oldtty attributes
    }

    // implied else, set_blocking successful


    char receivebuffer [20];



    // implied else, read successful
    //initialize parameter
    unsigned char A5A5[2];A5A5[0]=0xA5;A5A5[1]=0xA5;

    int old_data=0;int new_data=0;
    int delta;
    class odometer test1;
    unsigned char var[4];//for saving 4bytes raw data

    while(1){
        write (fd,A5A5 , 2);

        usleep (3000);
        if( 6> read (fd, receivebuffer, sizeof receivebuffer) ){ // then read failed
            return -1;
            break;
        }
        /*printf("value of buffer is %2d %2d %2d %2d %2d %2d \n\n",
        receivebuffer[0],
        receivebuffer[1],
        receivebuffer[2],
        receivebuffer[3],
        receivebuffer[4],
        receivebuffer[5]
        );*/  //here is test output,output like E1 9B FE FF FF 79
        for(int i=0;i<4;i++){
            var[i]=receivebuffer[i+1];
        }


        old_data=new_data;
        if(receivebuffer[5]!=receivebuffer[0]+receivebuffer[1]+receivebuffer[2]+receivebuffer[3]receivebuffer[4]){
            continue;
        }
        new_data=(var[3]<<24)|(var[2]<<16)|(var[1]<<8)|(var[0]);

        delta=new_data-old_data;
        test1.odo_add_mm(delta/revolution);
        test1.odo_print();
    }
    // cleanup

    tcsetattr (fd, TCSANOW, &oldtty);
    return 0;
} // end function: main
