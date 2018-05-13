#include "common.h"
#include "car_control.h"
#include "img_with_matrx.h"
#include "arm_math.h"
extern float32_t set_speed;
extern float32_t err;
extern uint8 mode;
uint16 FULL_ACC=30;

float delta_speed;

float setspeed=20;  //////
float l_set=0;
float r_set=0;
float l_speed_err0=0;
float l_speed_err1=0;
float l_speed_err2=0;
float r_speed_err0=0;
float r_speed_err1=0;
float r_speed_err2=0;
float e0=0;
float e1=0;
float e2=0;
float stree_max=7.45;
float stree_mid=6.84;
float stree_min=6.10;

/*拨码开关状态检测/
void DIPSwitch_State(void)
{
    uint8 DIPSwitch_buff[4]={1,1,1,1};
  
    *DIPSwitch_buff++=gpio_get(PTA5);
    *DIPSwitch_buff++=gpio_get(PTA7);
    *DIPSwitch_buff++=gpio_get(PTE25);
    *DIPSwitch_buff++=gpio_get(PTE27); 
}*/
//float curvature_calculate(struct P point1,struct P point2,struct P point3)
//{
 //   double S;
 //   double L1,L2,L3;
//    int16 x1,y1,x2,y2,x3,y3;
//    double curva;
//    x1=point1.x;
 //   x2=point2.x;
//    x3=point3.x;
//    y1=point1.y;
////    y3=point3.y;
    
//    L1=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
 //   L2=sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2));
//    L3=sqrt((x3-x1)*(x3-x1)+(y3-y1)*(y3-y1));
    
 //   S=(float)(1.0*((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1))/2);
    
 //   curva=10*4*S/L1/L2/L3;   
    
 //   return curva;/
/*小车控制程序*/

void stree_control(float stree)
{
  stree+=stree_mid;
 if(stree>stree_max)
   stree=stree_max;
 if(stree<stree_min)
   stree=stree_min;
 ftm_pwm_duty(FTM0, FTM_CH3,stree);
 delta_speed=0;                //差速
 if(stree>stree_mid)
 { l_set=setspeed-delta_speed/2;
   r_set=setspeed+delta_speed/2;
 }
 else
 { 
   l_set=setspeed-delta_speed/2;
   r_set=setspeed+delta_speed/2;
 }
}
void speed_control(void)
{  float Kp = 0.338659;  //比例因子                                          
   float Ki = 0.492012;  //积分因子  
   float Kd = 0.035660;  //微分因子  
  float l_out=0;
  float r_out=0;
  //get_speed();
 l_out=l_out+l_speed_err0+Kp*(l_speed_err0-l_speed_err1)+Ki*l_speed_err0+Kd*(l_speed_err0-2*l_speed_err1+l_speed_err2);
 r_out=r_out+r_speed_err0+Kp*(r_speed_err0-r_speed_err1)+Ki*r_speed_err0+Kd*(r_speed_err0-2*r_speed_err1+r_speed_err2);
 if(l_out>100)
   l_out=100;
 if(l_out<0)
   l_out=0;
 if(r_out>100)
   r_out=100;
 if(r_out<0)
   r_out=0;
 ftm_pwm_duty(FTM3, FTM_CH0,r_out);
 ftm_pwm_duty(FTM3, FTM_CH7,l_out);
}

void car_control(void)
{ 
   float stree=0;
   float Kp = 0.03;  //比例因子                                          
   float Kd = 0;  //微分因子 
   
     
   stree=stree+Kp*e0+Kd*(e0-2*e1+e2);
   e2=e1;
   e1=e0;
   e0=err;
   stree_control(stree);
   if(mode==1)
   {
     ftm_pwm_duty(FTM3, FTM_CH0,FULL_ACC);
     ftm_pwm_duty(FTM3, FTM_CH7,FULL_ACC);
   } 
   if(mode==2)
   {
    speed_control();

   }
}