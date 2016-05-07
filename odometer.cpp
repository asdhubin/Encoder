#include "odometer.h"
/**odometer::odometer(int baud_,float convolution_,std::string &port)
*���캯������ʼ��ʱ���벨����,��������ֵ/ʵ�ʾ��루mm���ı�ֵ,���ڶ˿���������"/dev/ttyUSB0"
*����:
*odometer test1={9600,500,"/dev/ttyUSB0"};//�趨������9600����������ֵÿ����500С��ǰ��1mm�����ӿ���"/dev/ttyUSB0"
*/
odometer::odometer(int baud_,float convolution_=1000,std::string &port){
    baud=baud_;
    convolution=convolution_;
    portname=port;
}
/**
*odometer::bind_port(std::string &port)
*�����趨portname��Ա
*/
void odometer::bind_port(std::string &port){
    portname=port;
}

/**odometer::speed()
*�����ٶ�ֵ����λ��mm/s
*/
float odometer::speed(){
    return speed;
}
/**float odometer::read_forward()
*����ǰ�����ľ������ֵ����λmm
*/
float odometer::read_forward(){
    return positive_kilometer*1000000+positive_meter*1000+positive_milimeter;
}
/**float odometer::read_backward()
*���غ��˹��ľ������ֵ����λmm
*/
float odometer::read_backward(){
    return negative_kilometer*1000000+negative_meter*1000+negative_milimeter;
}
/**float odometer::displacement()
*���ص�ǰλ�ƣ�������������λmm
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
    int a=m;//ȡ��
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




