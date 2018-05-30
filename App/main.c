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
 *  @brief      main����
 *  @since      v1.0
 *  @note       С���������
 */
uint8 imgbuff[CAMERA_SIZE];                             //����洢����ͼ�������
uint8 img[CAMERA_W*CAMERA_H]; //����洢��ѹ���ͼ�����飨���ڶ�ȡ����ֵ��ͼ����
extern float32_t set_speed;
extern float32_t err;
void PORTA_IRQHandler();
void DMA0_IRQHandler();
void PIT0_IRQHandler();
void PIT3_IRQHandler();
//typedef struct   
// {    
 //   uint16_t    a[60];        
 //   }my_data_t;       
//flash_data_t data;

void main(void)
{
    Site_t site     = {0, 0};                           //��ʾͼ�����Ͻ�λ��
    Size_t imgsize  = {CAMERA_W, CAMERA_H};             //ͼ���С
    Size_t size;                                       //��ʾ����ͼ���С
    size.H = LCD_H;
    size.W = LCD_W;

    uint8 i;
    
    DisableInterrupts;//��ֹ�����ж�
    DELAY_MS(100); 
  
    All_init();
  
    EnableInterrupts;//ʹ���ж�
   //  for(i=0;i<5;++i)
  //  {
   //   camera_get_img();
   //   img_extract((int8_t *)img,(uint8*)imgbuff,CAMERA_SIZE);//ͼ�����ݽ�ѹ
   // }
    
     DELAY_MS(100); 
    while(1)
    {
      camera_get_img();
      
      //if(DIPSwitch_buff&0x01)
        //lcd_img_binary_z(site, size, imgbuff, imgsize,BLACK,WHITE); //LCD��ʾ
    
      //vcan_sendimg(imgbuff,CAMERA_SIZE);
      
      img_extract((int8_t *)img,(uint8*)imgbuff,CAMERA_SIZE);//ͼ�����ݽ�ѹ
      
      imgprocess();//ͼ���� 
      
      lcd_display();
    }
}

/*****�ܿ���*****/
void PIT0_IRQHandler(void)
{
    car_control();
    PIT_Flag_Clear(PIT0);
}
