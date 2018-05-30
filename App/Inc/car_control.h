#ifndef _CARCONTROL_H_
#define _CARCONTROL_H_

typedef struct
{         
      float32_t e[3];         /**< The state array of length 3. */    
      float32_t p;               /**< The proportional gain. */     
      float32_t i;               /**< The integral gain. */     
      float32_t d;               /**< The derivative gain. */      
}pid;
void car_control(void);
void control_init(void);
extern uint32 l_speed;
extern uint32 r_speed;
#endif