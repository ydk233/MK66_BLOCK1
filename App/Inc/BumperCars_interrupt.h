#ifndef _BumperCars_Interrupt_H_
#define _BumperCars_Interrupt_H_

void PORTA_IRQHandler(void);
void DMA0_IRQHandler(void);
void PIT3_IRQHandler(void);
extern void PIT0_IRQHandler(void);
#endif