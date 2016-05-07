#include "odometer.h"
/**odometer::odometer(int baud_,float convolution_,std::string &port)
*构造函数，初始化时填入波特率,编码器数值/实际距离（mm）的比值,串口端口名，例如"/dev/ttyUSB0"
*举例:
*odometer test1={9600,500,"/dev/ttyUSB0"};//设定波特率9600，编码器数值每增加500小车前进1mm，连接口是"/dev/ttyUSB0"
*/
odometer::odometer(int baud_,float convolution_=1000,std::string &port){
    baud=baud_;
    convolution=convolution_;
    portname=port;
}
/**
*odometer::bind_port(std::string &port)
*单独设定portname成员
*/
void odometer::bind_port(std::string &port){
    portname=port;
}

/**odometer::speed()
*返回速度值，单位是mm/s
*/
float odometer::speed(){
    return speed;
}
/**float odometer::read_forward()
*返回前进过的距离绝对值，单位mm
*/
float odometer::read_forward(){
    return positive_kilometer*1000000+positive_meter*1000+positive_milimeter;
}
/**float odometer::read_backward()
*返回后退过的距离绝对值，单位mm
*/
float odometer::read_backward(){
    return negative_kilometer*1000000+negative_meter*1000+negative_milimeter;
}
/**float odometer::displacement()
*返回当前位移（有正负），单位mm
*/
float odometer::displacement(){
    return (positive_kilometer-negative_kilometer)*1000000+(positive_meter-negative_meter)*1000+(positive_milimeter-negative_milimeter);
}


/**
*void odo_add_mm()
*add XX milimeters to odometer
*/
void odometer::odo_add_mm(float mm){
    if(mm>=0){
        positive_milimeter+=mm;
        positive_meter    +=positive_milimeter/1000;
        positive_kilometer =positive_meter/1000;
        positive_meter     =positive_meter%1000;
        positive_milimeter =positive_milimeter%1000;
    }
    else if(mm<0){
        negative_milimeter+=mm;
        negative_meter    +=negative_milimeter/1000;
        negative_kilometer =negative_meter/1000;
        negative_meter     =negative_meter%1000;
        negative_milimeter =negative_milimeter%1000;
    }
}
/**
*void odo_add_m()
*add XX meters to odometer
*/
void odometer::odo_add_m(float m){
    int a=m;//取整
    if(m>=0){
        positive_milimeter+=(m-a)*1000;
        positive_meter     = positive_meter + a +(positive_milimeter/1000);
        positive_kilometer = positive_meter/1000;
        positive_meter     = positive_meter%1000;
        positive_milimeter = positive_milimeter%1000;
    }
    else if(m<0){
        negative_milimeter+=(m-a)*1000;
        negative_meter     = negative_meter + a +(negative_milimeter/1000);
        negative_kilometer = negative_meter/1000;
        negative_meter     = negative_meter%1000;
        negative_milimeter = negative_milimeter%1000;
    }
}
/**
*void odo_print()
*print both forward distance and backward distance.
*/
void odometer::odo_print(){
    std::cout<<"move forward "<<positive_kilometer<<"km "<<positive_meter<<"m "
    <<positive_milimeter<<"mm"<<std::endl;
    std::cout<<"move back    "<<negative_kilometer<<"km "<<negative_meter<<"m "
    <<negative_milimeter<<"mm"<<std::endl;
}
/**
*void odo_print_positive()
*only print forward distance.
*/
void odometer::odo_print_positive(){
    std::cout<<"move forward "<<positive_kilometer<<"km "<<positive_meter<<"m "
    <<positive_milimeter<<"mm"<<std::endl;
}
/**
*void odo_print_negative()
*only print backward distance.
*/
void odometer::odo_print_negative(){
    std::cout<<"move back    "<<negative_kilometer<<"km "<<negative_meter<<"m "
    <<negative_milimeter<<"mm"<<std::endl;
}




