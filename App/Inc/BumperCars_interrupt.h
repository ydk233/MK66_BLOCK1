#ifndef _BumperCars_Interrupt_H_
#define _BumperCars_Interrupt_H_

void PORTA_IRQHandler(void);
void DMA0_IRQHandler(void);
void PIT3_IRQHandler(void);
extern void PIT0_IRQHandler(void);
extern uint32 n_L,n_R;//�����ȫ�ֱ���
extern uint8 Dir_L,Dir_R;//�����ȫ�ֱ���
#endif