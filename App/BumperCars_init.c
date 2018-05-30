#include "common.h"
#include "include.h"

/*初始化所有*/
extern void control_init(void);
extern void PORTA_IRQHandler(void);
extern void DMA0_IRQHandler(void);

extern  uint8 imgbuff[CAMERA_SIZE];  

void All_init(void)
{
    sensor_init();
    interrupt_init();
    control_init();
    
}

/*传感器初始化*/
void sensor_init(void)
{       
    //禁止中断
    disable_irq(PORTA_IRQn);
    disable_irq(DMA0_DMA16_IRQn);
    disable_irq(PIT0_IRQn);
  
    //舵机初始化
    ftm_pwm_init(FTM0, FTM_CH3,50,6.89,FTM0_CH3_PIN);//精度10000u，舵机居中
  
    //电机初始化
    ftm_pwm_init(FTM3, FTM_CH0,10*1000,20,FTM3_CH0_PIN);        
    ftm_pwm_init(FTM3, FTM_CH1,10*1000,0,FTM3_CH1_PIN);
    ftm_pwm_init(FTM3, FTM_CH6,10*1000,0,FTM3_CH6_PIN);
    ftm_pwm_init(FTM3, FTM_CH7,10*1000,20,FTM3_CH7_PIN);
    gpio_init(PTE3,GPO,1);
    gpio_init(PTE4,GPO,1 );  
  
    //编码器初始化
    ftm_input_init(FTM1,FTM_CH0,FTM_Rising,FTM_PS_1,FTM1_CH0_PIN);
    ftm_input_init(FTM2,FTM_CH1,FTM_Rising,FTM_PS_1,FTM2_CH1_PIN);
    port_init_NoALT(FTM1_CH0_PIN,PULLUP);
    port_init_NoALT(FTM2_CH1_PIN,PULLUP);                        
    gpio_init(PTA10,GPI,1);
    gpio_init(PTA9, GPI,1);                                     
  
    //拨码开关初始化
    gpio_init(PTA5, GPI,1);
    gpio_init(PTA7, GPI,1);
    gpio_init(PTE25,GPI,1);
    gpio_init(PTE27,GPI,1);
  
    lcd_init(RED);
  
    camera_init(imgbuff); 
}

/*****中断初始化*****/
void interrupt_init(void)
{
    set_vector_handler(PORTA_VECTORn ,PORTA_IRQHandler);
    set_vector_handler(DMA0_DMA16_VECTORn , DMA0_IRQHandler);
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);
    set_vector_handler(PIT3_VECTORn ,PIT3_IRQHandler);//编码器控制

    NVIC_SetPriority(PORTA_IRQn,0);
    NVIC_SetPriority(PIT0_IRQn,1);
    NVIC_SetPriority(DMA0_DMA16_IRQn,2);
    NVIC_SetPriority(PIT3_IRQn,3);
    
    pit_init_ms(PIT3,50);
    pit_init_ms(PIT0,1);
    
    
    enable_irq(PORTA_IRQn);
    enable_irq(DMA0_DMA16_IRQn);
    enable_irq(PORTD_IRQn);
    enable_irq(PIT3_IRQn);
    enable_irq(PIT0_IRQn);

}
