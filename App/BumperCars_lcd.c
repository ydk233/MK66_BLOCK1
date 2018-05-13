#include "common.h"
#include "BumperCars_lcd.h"
#include "img_with_matrx.h"
 Site_t  my_site0={0,0};   //LCD显示图像的位置
 Size_t  my_size0={CAMERA_W,CAMERA_H};   //LCD显示图像的大小
 Size_t  my_zoomimgsize0={80,60};
 extern uint8 imgbuff[CAMERA_SIZE];
 extern uint8 minrow;
 extern int32 feature[CAMERA_H];
void lcd_display()
{lcd_img_binary_z(my_site0, my_size0, imgbuff, my_zoomimgsize0,BLACK,WHITE); //LCD显示
 uint8 i;
 Site_t t;
 t.x=100;
 t.y=10;
 lcd_num_c(t,feature[minrow],BLUE,RED);
 
 Site_t t1;
 t1.y=minrow;
 for(i=0;i<80;++i)
 {
   t1.x=i;
    lcd_point(t1,BLUE);
 }
}