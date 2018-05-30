#include "common.h"
#include "include.h"
#include "img_with_matrx.h"
#include "arm_math.h"
#include "BumperCars_interrupt.h"

extern uint8 mode;
extern float32_t a;
extern float32_t b;
extern uint32 n_L,n_R;//�����ȫ�ֱ���
extern uint8 Dir_L,Dir_R;//�����ȫ�ֱ���

float32_t a_=0;
float64_t st=0;
float32_t l_out=0;
float32_t r_out=0;
uint32 l_speed;
uint32 r_speed;
uint16 FULL_ACC=30;
float l_set=0;
float r_set=0;
float setb=0;
float stree=0;
float delta_speed;
float setspeed=40000;  //////
float stree_max=7.55;
float stree_mid=6.89;
float stree_min=6.25;
pid sa;
pid sb;
pid sl;
pid sr;

void control_init(void)
{
   memset(sa.e, 0, 3U * sizeof(float32_t));
   memset(sb.e, 0, 3U * sizeof(float32_t));
   sb.p=3;    //b���Ʋ�����Ŀǰ���ã�
   sb.i=0;
   sb.d=0;
   
   sa.p=0.0137;    //now is perfect 0.0135
   sa.i=0;
   sa.d=0.;
  
   sl.p = 0.005;    //������Ʋ�����ע������һ��              
   sl.i = 0.0; 
   sl.d = 0.0;
  
   sr.p = 0.005;                                         
   sr.i = 0.00;    
   sr.d = 0.0;
}
void get_speed(void)
{ 
  l_speed=n_L;
  r_speed=n_R;
 
}
void stree_control(void)      
{
  float stree;
  //sb.e[0]=0;//˫�ջ�����
 
  sb.e[0]=setb-b;
  a_+=sb.p*(sb.e[0]-sb.e[1])+sb.d*(sb.e[0]-2*sb.e[1]+sb.e[2]);
  sa.e[0]=-a_+a;
  if(sa.e[0]>50)
    sa.e[0]=50;
  if(sa.e[0]<-50)
    sa.e[0]=-50;
  st+=sa.p*(sa.e[0]-sa.e[1])+sa.d*(sa.e[0]-2*sa.e[1]+sa.e[2]);
  sb.e[2]=sb.e[1];
  sb.e[1]=sb.e[0];
  sa.e[2]=sa.e[1];
  sa.e[1]=sa.e[0];

  if(st>stree_max-stree_mid)//�޷�
    st=stree_max-stree_mid;
  if(st<stree_min-stree_mid)
    st=stree_min-stree_mid;  
 stree=st+stree_mid;
 ftm_pwm_duty(FTM0, FTM_CH3,stree);
 delta_speed=0;                //����
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
 
 // get_speed();
  sl.e[0]=l_set-l_speed;
  sr.e[0]=r_set-r_speed;
 l_out+=sl.p*(sl.e[0]-sl.e[1])+sl.d*(sl.e[0]-2*sl.e[1]+sl.e[2]);
 r_out+=sr.p*(sr.e[0]-sr.e[1])+sr.d*(sr.e[0]-2*sr.e[1]+sr.e[2]);
  sl.e[2]=sl.e[1];
  sl.e[1]=sl.e[0];
  sr.e[2]=sr.e[1];
  sr.e[1]=sr.e[0];
 if(l_out>30)
   l_out=30;
 if(l_out<0)
   l_out=0;
 if(r_out>30)
   r_out=30;
 if(r_out<0)
   r_out=0;
 ftm_pwm_duty(FTM3, FTM_CH0,r_out);
 ftm_pwm_duty(FTM3, FTM_CH7,l_out);
}

void car_control(void)
{ 
   get_speed();
   stree_control();
   
   if(mode==1)
   {
     ftm_pwm_duty(FTM3, FTM_CH0,FULL_ACC);
     ftm_pwm_duty(FTM3, FTM_CH7,FULL_ACC);
   } 
   if(mode==2)
   {
    //speed_control();
   ftm_pwm_duty(FTM3, FTM_CH0,FULL_ACC);
   ftm_pwm_duty(FTM3, FTM_CH7,FULL_ACC);
   }
}