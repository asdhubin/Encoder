#ifndef ODOMETER_H_INCLUDED
#define ODOMETER_H_INCLUDED
/**
*class odometer
*km,m,mm
*/
#include <iostream>
#include <string>
#include "serialport"
class odometer{
private:
    int positive_kilometer=0;
    int positive_meter=0;
    float positive_milimeter=0;
    int negative_kilometer=0;
    int negative_meter=0;
    float negative_milimeter=0;

    std::string portname;
    float convolution;
    int baud;

public:
    float speed;//速度放在这边方便主程序中实时写入/读取速度
    odometer();
    odometer(int baud_,float convolution_,std::string &port);
    ~odometer();
    void odo_add_mm(float mm);
    void odo_add_m(int m);
    void odo_print();
    void odo_print_positive();
    void odo_print_negative();
    void bind_port(std::string &port);
    float speed();
    float read_forward();
    float read_backward();
    float displacement();
    int start();


#endif // ODOMETER_H_INCLUDED
