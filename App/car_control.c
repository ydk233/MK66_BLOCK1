#include "common.h"
#include "car_control.h"
#include "img_with_matrx.h"
#include "arm_math.h"
extern uint8 mode;
extern float32_t a;
extern float32_t b;
float32_t a`=0;
float32_t st=0;
float32_t l_out=0;
float32_t r_out=0;
uint16 FULL_ACC=30;
float delta_speed;
float setspeed=20;  //////
float l_set=0;
float r_set=0;
pid *sa;
pid *sb;
pid *sl;
pid *sr;
float stree_max=11.175;
float stree_mid=10.26;
float stree_min=9.15;
float stree=0;


void stree_control(void)      
{
  float stree;
  sb.e[0]=setb-b;//双闭环控制
  a`+=sb.p*(sb.e[0]-sb.e[1])+sb.d*(sb.e[0]-2*sb.e[1]+sb.e[2]);
  sa.e[0]=a`-a;
  st+=sa.p*(sa.e[0]-sa.e[1])+sa.d*(sa.e[0]-2*sa.e[1]+sa.e[2]);
  sb.e[2]=sb.e[1];
  sb.e[1]=sb.e[0];
  sa.e[2]=sa.e[1];
  sa.e[1]=sa.e[0];
  stree=st+stree_mid;
  if(stree>stree_max)//限幅
    stree=stree_max;
  if(stree<stree_min)
    stree=stree_min;
 ftm_pwm_duty(FTM0, FTM_CH3,stree);
 delta_speed=0;                //差速
 if(st>stree_mid)
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
{  
 
  get_speed();
  sl.e[0]=
  sr.e[0]=
 l_out+=sl.p*(sl.e[0]-sl.e[1])+sl.d*(sl.e[0]-2*sl.e[1]+sl.e[2]);
 r_out+=sr.p*(sr.e[0]-sr.e[1])+sr.d*(sr.e[0]-2*sr.e[1]+sr.e[2]);
  sl.e[2]=sl.e[1];
  sl.e[1]=sl.e[0];
  sr.e[2]=sr.e[1];
  sr.e[1]=sr.e[0];
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
   sb.p=0.01;
   sb.i=0;
   sb.d=0;
   sa.p=0.01;
   sa.i=0;
   sa.d=0;
   sl.p = 0.338659;                                        
   sl.i = 0.492012; 
   sl.d = 0.035660;
   sr.p = 0.338659;                                         
   sr.i = 0.492012;    
   sr.d = 0.035660;
   stree_control();
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
