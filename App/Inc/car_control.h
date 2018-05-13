#include "common.h"
#include "img_with_matrx.h"
#include "arm_math.h"
void car_control(void);
extern float curvature_get();
extern float32_t set_speed;
extern float32_t err;
extern uint8 mode;
extern float l_speed_err[3];
extern float r_speed_err[3];
extern float l_set;
extern float r_set;