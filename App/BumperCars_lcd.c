#include "common.h"
#include "BumperCars_lcd.h"
#include "img_with_matrx.h"
#include "include.h"
#include "enter.h"
#include "BumperCars_interrupt.h"
#include "car_control.h"
 Site_t  my_site0={0,0};   //LCD显示图像的位置
 Size_t  my_size0={CAMERA_W,CAMERA_H};   //LCD显示图像的大小
 Size_t  my_zoomimgsize0={80,60};
 extern uint8 imgbuff[CAMERA_SIZE];
 extern uint8 flagrow;
 extern float feature[CAMERA_H][3];
 extern float32_t a;
 extern float32_t b;
 extern int16 f;
 extern uint32 l_speed;
 extern uint32 r_speed;
 extern uint8 l_upside;
 extern uint8 r_upside;
 char buff[20];
 char buff1[20];
void lcd_display()
{
  lcd_img_binary_z(my_site0, my_size0, imgbuff, my_zoomimgsize0,BLACK,WHITE); //LCD显示
  uint8 i;
  Site_t t;
  t.x=100;
  t.y=10;
  lcd_snum_c(t,f,BLUE,RED);
           

  Site_t t1;
  t1.y=flagrow;
  for(i=0;i<80;++i)
   {
     t1.x=i;
    lcd_point(t1,BLUE);
   }
  Site_t t2;
  for(i=5;i<55;++i)
   {
    t2.y=i;
    if(feature[i][0]>40)
      t2.x=79;
    else if(feature[i][0]<-40)
      t2.x=0;
    else
       t2.x=feature[i][0]+40;
    lcd_point(t2,RED);
  }
   Site_t t3;
  t3.x=10;
  t3.y=100;
  lcd_snum_c(t3,l_speed,BLUE,RED);
  
  Site_t t4;
  t4.x=60;
  t4.y=100;
  lcd_snum_c(t4,r_speed,BLUE,RED);
  
  Site_t t5;
  t5.x=90;
  t5.y=30;
  sprintf(buff,"%.1f",a);    
  lcd_str(t5, buff, BLUE, RED);
  
  Site_t t6;
  t6.x=90;
  t6.y=50;
  sprintf(buff1,"%.1f",b);    
  lcd_str(t6, buff1, BLUE, RED);
//  lcd_snum_c(t5,a,BLUE,RED);
   
}