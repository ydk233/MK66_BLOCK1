#ifndef _BumperCars_Control_H_
#define _BumperCars_Control_H_
struct P
{
    int x;
    int y;
};
void DIPSwitch_State(void);
void car_control(void);
extern float curvature_get();
#endif