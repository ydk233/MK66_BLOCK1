#include "common.h"
#include "include.h"
#include "arm_math.h"
#include "img_with_matrx.h"


extern uint8 imgbuff[CAMERA_SIZE];                             
extern uint8 img[CAMERA_H][CAMERA_W];

float set_speed;
/////////图像处理/////////
int16 f;
uint8 mode=1;
uint8 minrow=55;
//uint32 blocksize=CAMERA_W/2;
uint8 maxrow=5;
uint8 flagrow=20;
//uint8 deadline=25;
float feature[60][3];
uint8 threshold_bottom=3;
uint8 threshold_top=7;
uint8 inil=39;
uint8 inir=40; 
//uint16 bias[60];         //偏置，丢边时使用
//uint8 width[5][2];
uint8 n=255;
uint8 max=0;
uint8 min=59;
uint8 threshold_mov=10;
//uint8 cir_row=0;
//uint8 circult;
uint8 l_downside=0;
uint8 r_downside=0;
uint8 l_upside=0;
uint8 r_upside=0;
////////最小二乘//////////   

float32_t a;
float32_t b;

/*循迹函数*/
void find_the_feature()
{
  uint8 i=55;
  uint8 t=maxrow;
  uint8 l;
  uint8 ll;
  uint8 r;
  uint8 rl;         //左右指针及上一位指针
  uint8 flagl=inil;
  uint8 flagr=inir;   //左右结果
  float Y;          //中值
  uint8 k=0;
  int16 delta_flag=40;
 for(;i>5;--i)
  {
    l=img[i][flagl];
    r=img[i][flagr];
    ll=img[i][flagl];
    rl=img[i][flagr];
   while(l+ll!=255)   
    {
 
      if(l==0)     //黑，右扫描
        {
          if(flagl==79)
            break;
          ll=l;
          ++flagl;
          l=img[i][flagl];
          
          continue;
        }
      if(l==255)   //白，左扫描
      {
        if(flagl==0)
           break;
        ll=l;
        --flagl;
        l=img[i][flagl];
        
        continue;
      }
    }
     while(r+rl!=255)
    {
 
      if(r==0)    //黑，左扫描
        {
          if(flagr<=0)
            break;
          rl=r;
          --flagr;
          r=img[i][flagr];
          
          continue;
        }
      if(r==255)    //白，右扫描
      {
        if(flagr==79)
            break;
        rl=r;
        ++flagr;
        r=img[i][flagr];
        continue;
      }
    } 
   delta_flag=flagr-flagl;
   if(delta_flag<3)
      break;
   if((flagr==79)&&(flagl==0))
     {  
       Y=0;
       min=i;
     }

   else if((flagr==79)&&(flagl>15))
     //Y=flagl+bias[i]-40;
     Y=flagl+30-40;
   else if((flagl==0)&&(flagr<65))
     //Y=flagr-bias[i]-40;     //丢边处理
     Y=flagr-30-40;
   else
   Y=(flagl+flagr)/2-40;
   feature[i][0]=Y;
   feature[i][1]=flagl;
   feature[i][2]=flagr;
   //if((flagl==0)&&(flagr==79)&&(i>30)&&(n==255))
    //  minrow=i;
   //if((mode==0)&&(i==n-k)&&(k<5)&&(n!=255))
  // {
   //  width[k][0]=i;
   //  width[k][1]=flagr-flagl;
  //   ++k;
 //  }
   if (i==minrow)    //左右标初始化
    {
      inil=flagl;
      inir=flagr;
    }
  if(i==flagrow)                //圆环识别
   {
     if(flagl>flagr)
     feature[i][0]=40;
   } 
  
   max=i;
  }
    
     
 
}
  

void casual_time(uint8 minrow)
{       
  float s_x2;
  float s_y;
  float s_x;
  float s_xy;
  float N=9;
  s_x2=9600;
  s_x=270;
  s_y=feature[10][0]+feature[15][0]+feature[20][0]+feature[25][0]+feature[30][0]+feature[35][0]+feature[40][0]+feature[45][0]+feature[50][0];
  s_xy=0*feature[10][0]+45*feature[15][0]+40*feature[20][0]+35*feature[25][0]+30*feature[30][0]+25*feature[35][0]+20*feature[40][0]+15*feature[45][0]+10*feature[50][0];
  if (N*s_x2!=s_x*s_x)
  
    a=(N*s_xy-s_x*s_y)/(N*s_x2-s_x*s_x);
  
  mode=1;
}
void emergency(uint8 minrow)
{
  float s_x2=0;
  float s_y=0;
  float s_x=0;
  float s_xy=0;
  float N=0;
  uint8 i;
  if(max>25)
  {
    for(i=min;i>max;--i)
    {
      s_x2+=(60-i)*(60-i);
      s_x+=(60-i);
      s_y+=feature[i][0];
      s_xy+=(60-i)*feature[i][0];
      ++N;
    }
  }
  else
  {
    s_x2=3055;
    s_x=135;
    s_y=feature[40][0]+feature[39][0]+feature[38][0]+feature[37][0]+feature[36][0]+feature[35][0];
    s_xy=20*feature[40][0]+21*feature[39][0]+22*feature[38][0]+23*feature[37][0]+24*feature[36][0]+25*feature[35][0];
    N=6;
    
  }
  if (N*s_x2!=s_x*s_x)
    a=50*(N*s_xy-s_x*s_y)/(N*s_x2-s_x*s_x);
  
  a+=r_upside-l_upside;
  mode=2;
}
 
void trigger_check(void)
{
  uint8 i;
  for(i=54;i>max+1;i--)
  {
    if((feature[i][1]==0)&&(feature[i+1][1]>threshold_mov))
        l_downside=i;
    if((feature[i][2]==79)&&(feature[i+1][2]>80-threshold_mov))
        r_downside=i;
    if((feature[i][1]==0)&&(feature[i-1][1]>threshold_mov))
        l_upside=i;
    if((feature[i][2]==79)&&(feature[i-1][2]>80-threshold_mov))
        r_upside=i;
  }
}
void imgprocess()
{
 
  uint16 c;
  find_the_feature();
 //Q trigger_check();
  f=feature[flagrow][0];
  c=abs(f);
  if(mode==1)
    {
      if((c<threshold_top)&&(flagrow>max))
        casual_time(minrow);  //直道正常情况
      else
        emergency(minrow);    //弯道等情况
    }
  if(mode==2)
    {
      if((c<threshold_bottom)&&(flagrow>max))
        casual_time(minrow);
      else
        emergency(minrow);
    }
  b=feature[35][0];
}


//void bias_init()
//{
//  float a1;
//  float b1;
//  uint16 s_x2=0;
//  int16 s_y=0;
//  uint16 s_x=0;
//  int16 s_xy=0;
//  uint8 N=5;
//  uint8 i;
//  find_the_feature(0);
//  for(i=0;i<5;i++)
//  {
//    s_x2+=width[i][0]*width[i][0];
//    s_x+=width[i][0];
 //   s_y+=width[i][1];
//    s_xy+=width[i][0]*width[i][1];
//  }
//  b1=(s_x2*s_y-s_x*s_xy)/(N*s_x2-s_x*s_x);
//  a1=(N*s_xy-s_x*s_y)/(N*s_x2-s_x*s_x);  
//  for(i=0;i<60;++i)
//    bias[i]=(a1*i+b1)/2;
//}



  