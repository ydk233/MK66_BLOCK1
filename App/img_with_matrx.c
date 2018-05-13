#include "common.h"
#include "include.h"
#include "BumperCars_control.h"

uint8 imgbuff[CAMERA_SIZE];                             //定义存储接收图像的数组
uint8 img[CAMERA_H][CAMERA_W];



#define uint32_t blocksize=CAMERA_W;
#define uint8 maxrow=50;
#define uint8 deadline=25;
extern float_32_t set_speed;
extern float_32_t err;
float_32_t weights[CAMERA_W];
float_32_t feature[CAMERA_H];
float_32_t threshold_bottom=5;
float_32_t threshold_top=10;
float_32_t out;   

 
void get_weights()
{
  for(n=0;n<30;++n)
    weights[n]=n;
  for(n=0;n<30;++n)
    weight[59-n]=-n;
}

void find_the_feature (uint8 i)
{
  float_32_t feature;
  arm_dot_prod_f32(&img[i][0],&weights,blocksize,&feature[i]);
  }
  
void imgprocess()
{
  uint8 minrow=5;
  get_weights();
  if ((abs(find_the_feature(minrow))<threshold_bottom)and(minrow<59))
    ++minrow;
    else if (abs(find_the_feature(minrow))<threshold_top)and(minrow>5)
      --minrow;
  
if(minrow<deadline)
   casual_time(minrow);
else
   emergency(minrow);
}

void casual_time(uint8 minrow)
{uint16 s_x2=0;
  uint16 s_y=0;
  uint16 s_x=0;
  uint16 s_xy=0;
  uint8 N=0;
  float a;
  for(n=minrow;n<maxrow;n=n+3)
  { find_the_feature(n);
    s_x2+=n*n;
    s_x+=n;
    s_y+=feature[n];
    s_xy=feature[n]*n;
    ++N;
  }
  a=(N*s_xy-s_x*s_y)/(N*s_x2-s_x*s_x);
  err=a;
}
void emergency(uint8 minrow)
{float ave;
 uint16 sum=0;
  for(n=0;n<10;++n)
  {find_the_feature(minrow+n);
  sum+=feature[minrow+n];
  }
  ave=sum/10;
  err=ave;
}
  
  