#include "common.h"
#include "include.h"
/*****摄像头场中断*****/
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
    
    PIT_Flag_Clear(PIT3);
}