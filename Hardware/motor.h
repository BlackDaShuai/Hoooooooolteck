#ifndef __MOTOR_H
#define __MOTOR_H



extern int actionFlag;//小船运动标志位，0停止，1慢速前进，2快速前进，3左转，4右转，5倒车
extern int rollerFlag;//滚筒开关标志位，0关闭，1开启


void motorGPIOInit(void);
void motorInit(void);
void shipLeft(void);
void shipRight(void);
void shipGoFast(void);
void shipGoSlow(void);
void shipStop(void);
void shipBack(void);
void RollerOn(void);
void RollerOff(void);

void shipFunction(void);
void rollerFunction(void);

#endif


