
#include "led.h"

void led_init(void)
{
	CKCU_PeripClockConfig_TypeDef LEDClock = {{ 0 }};
	LEDClock.Bit.PC = 1; //ʹ��PC
	CKCU_PeripClockConfig(LEDClock, ENABLE); //һ��Ҫ��ʹ��ʱ�ӣ������������
	GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_15|GPIO_PIN_14, GPIO_DIR_OUT); //����PC15Ϊ���
	GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_14, SET);
	GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_15, SET);
	// led_off();
}

void led_on(void)//LED2�򿪣�LED1�ر�
{
   GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_15, RESET);
	 GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_14, SET);
}

void led_off(void)//LED1�򿪣�LED2�ر�
{
   GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_15, SET);
	 GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_14, RESET);
	
}

void lightline_Init(void)
{
	CKCU_PeripClockConfig_TypeDef LEDClock = {{ 0 }};
	LEDClock.Bit.PC = 1; //ʹ��PC
	CKCU_PeripClockConfig(LEDClock, ENABLE); //һ��Ҫ��ʹ��ʱ�ӣ������������
	GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_2, GPIO_DIR_OUT); //����PC15Ϊ���
	GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_2, RESET);
}

void lightline_Check(void)
{
	if(LF==1)
	GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_2, SET);
	else if(LF==0)
	GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_2, RESET);
}

