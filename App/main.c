/**********BumoerCars*********/
/**********BumoerCars*********/
/**********BumoerCars*********/
/**********BumoerCars*********/
/**********BumoerCars*********/


#include "common.h"
#include "include.h"
#include "enter.h"
#include "arm_math.h"
/*!
 *  @brief      main函数
 *  @since      v1.0
 *  @note       小车整体控制
 */

extern void imgprocess(void);


void PIT0_IRQHandler();
 uint8 imgbuff[CAMERA_SIZE];                             //定义存储接收图像的数组
 q7_t img[CAMERA_W*CAMERA_H]; //定义存储解压后的图像数组（用于读取像素值，图像处理）
extern float32_t set_speed;
extern float32_t err;
void PORTA_IRQHandler();
void DMA0_IRQHandler();
void PIT3_IRQHandler();

void main(void)
{
    Site_t site     = {0, 0};                           //显示图像左上角位置
    Size_t imgsize  = {CAMERA_W, CAMERA_H};             //图像大小
    Size_t size;                                       //显示区域图像大小
    size.H = LCD_H;
    size.W = LCD_W;

    DisableInterrupts;//禁止所有中断
    DELAY_MS(100); 
  
    All_init();
  
    EnableInterrupts;//使能中断
    //DIPSwitch_State();  //检查拨码开关状态
    //SCCB_WriteByte(OV7725_CNST, 0xff);
    while(1)
    {
      camera_get_img();
      
      //if(DIPSwitch_buff&0x01)
        //lcd_img_binary_z(site, size, imgbuff, imgsize,BLACK,WHITE); //LCD显示
      lcd_display();
      //vcan_sendimg(imgbuff,CAMERA_SIZE);
      
      img_extract((int8_t *)img,(uint8*)imgbuff,CAMERA_SIZE);//图像数据解压
      
      imgprocess();//图像处理
    }
}

/*****总控制*****/
void PIT0_IRQHandler(void)
{
    car_control();
    PIT_Flag_Clear(PIT0);
}
