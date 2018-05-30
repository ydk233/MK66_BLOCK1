#include "common.h"
#include "include.h"
#include "BumperCars_interrupt.h"
/*****摄像头场中断*****/
 uint32 n_L,n_R;//定义成全局变量
 uint8 Dir_L,Dir_R;//定义成全局变量
void PORTA_IRQHandler(void)
{
    uint8  n;
    uint32 flag;

    while(!PORTA_ISFR);
    flag = PORTA_ISFR;
    PORTA_ISFR  = ~0;

    n = 29;
    if(flag & (1 << n))
    {
        camera_vsync();
    }

}

/*****DMA中断*****/
void DMA0_IRQHandler(void)
{
    camera_dma();
}

/*****定时获取编码器数值中断*****/
void PIT3_IRQHandler(void)
 {
    
  //  nll=nl;
    //nrl=nr;
    n_L =ftm_input_get(FTM1,FTM_CH0);//PTA8 上编码器不知道连左电机还是右电机
    n_R =ftm_input_get(FTM2,FTM_CH1);//PTA11 下编码器
    //=nl-nll;
    //=nr-nrl;
    Dir_L=gpio_get(PTA10);      //上编码器
    Dir_R=gpio_get(PTA9);       //下编码器
    
    ftm_input_clean(FTM1);      
    ftm_input_clean(FTM2);      //清计数值
    //n_L=ftm_quad_get(FTM1);          //获取FTM 正交解码 的脉冲数(负数表示反方向)
   // n_R=ftm_quad_get(FTM2);
   // ftm_quad_clean(FTM1);
   // ftm_quad_clean(FTM2);
    
    PIT_Flag_Clear(PIT3);
}/*init文件中取消//enable_irq(PIT3_IRQn);注释*/
