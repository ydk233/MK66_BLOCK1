#include "common.h"
#include "include.h"
#include "arm_math.h"
#include "img_with_matrx.h"


extern uint8 imgbuff[CAMERA_SIZE];                             //定义存储接收图像的数组
extern uint8 img[CAMERA_H][CAMERA_W];
float set_speed;
float err=0;
uint8 mode;
uint8 minrow=20;

uint32 blocksize=CAMERA_W/2;
uint8 maxrow=50;
uint8 deadline=25;
int16 feature[60];
uint8 threshold_bottom=5;
uint8 threshold_top=100;
   
uint16 s_x2;
int16 s_y;
uint16 s_x;
int16 s_xy;
uint8 N;
int16 a;
int16 b;


int16 find_the_feature(uint8 i,uint8 t,uint8 step,uint8 mode)
{
  uint8 l;
  uint8 ll;
  uint8 r;
  uint8 rl;
  uint8 flagl=39;
  uint8 flagr=40;
  int16 Y;
  
  s_x2=0;
  s_y=0;
  s_x=0;
  s_xy=0;
  N=0;
  uint8 n=0;
  int16 ret;
  uint8 k; 
  for(k=0;k<t;k+=step)
  {
    l=img[i+k][flagl];
    r=img[i+k][flagr];
    ll=img[i+k][flagl];
    rl=img[i+k][flagr];
   while((l+ll!=255)&&(flagl<80)&&(flagl>0))
    {
 
      if(l==0)
        {
          ll=l;
          ++flagl;
          l=img[i+k][flagl];
          continue;
        }
      if(l==255)
      {
        ll=l;
        --flagl;
        l=img[i+k][flagl];
        continue;
      }
    }
     while((r+rl!=255)&&(flagr<80)&&(flagr>0))
    {
 
      if(r==0)
        {
          rl=r;
          --flagr;
          r=img[i+k][flagr];
          continue;
        }
      if(r==255)
      {
        rl=r;
        ++flagr;
        r=img[i+k][flagr];
        continue;
      }
    }
   ++n;
   }
   Y=flagl+flagr-79;
   feature[i+k]=Y;
   if(mode==1)
    {   
      s_x2+=(60-i-k)*(60-i-k);
      s_x+=(60-i-k);
      s_y+=Y;
      s_xy+=Y*(60-i-k);
      ++N;
    }
   
  if(mode==1)
    {
      b=(N*s_xy-s_x*s_y)/(N*s_x2-s_x*s_x);
      a=(N*s_xy-s_x*s_y)/(N*s_x2-s_x*s_x);
    }
    ret=feature[i+k];
    return ret;
     
 
}
  

void casual_time(uint8 minrow)
{
  find_the_feature(minrow,5,3,1);
  err=a*a+b*b;
  mode=1;
}
void emergency(uint8 minrow)
{
  
  find_the_feature(40,3,2,1);
  err=a*a+b*b;
  mode=2;
}
 
void imgprocess()
{
  int16 f;
  uint16 a;
  f=find_the_feature(minrow,1,1,0);
  a=abs(f);
  if(a<threshold_bottom)
    casual_time(minrow);
  else
    emergency(minrow);
}

  
