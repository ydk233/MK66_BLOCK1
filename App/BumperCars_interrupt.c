#include "common.h"
#include "include.h"
/*****����ͷ���ж�*****/
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

/*****DMA�ж�*****/
void DMA0_IRQHandler(void)
{
    camera_dma();
}

/*****��ʱ��ȡ��������ֵ�ж�*****/
void PIT3_IRQHandler(void)
{
    
    PIT_Flag_Clear(PIT3);
}