#ifndef __LED_H
#define __LED_H

#include "ht32f5xxxx_ckcu.h"
#include "ht32f5xxxx_gpio.h"

extern int LF;

void led_init(void);
void led_on(void);
void led_off(void);
void lightline_Init(void);
void lightline_Check(void);


#endif



