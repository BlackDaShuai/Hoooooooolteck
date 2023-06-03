#ifndef __MOTOR_H
#define __MOTOR_H



extern int actionFlag;//С���˶���־λ��0ֹͣ��1����ǰ����2����ǰ����3��ת��4��ת��5����
extern int rollerFlag;//��Ͳ���ر�־λ��0�رգ�1����


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


