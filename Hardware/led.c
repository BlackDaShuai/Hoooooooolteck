
#include "led.h"

void led_init(void)
{
	CKCU_PeripClockConfig_TypeDef LEDClock = {{ 0 }};
	LEDClock.Bit.PC = 1; //使能PC
	CKCU_PeripClockConfig(LEDClock, ENABLE); //一定要先使能时钟，再配置下面的
	GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_15|GPIO_PIN_14, GPIO_DIR_OUT); //设置PC15为输出
	GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_14, SET);
	GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_15, SET);
	// led_off();
}

void led_on(void)//LED2打开，LED1关闭
{
   GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_15, RESET);
	 GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_14, SET);
}

void led_off(void)//LED1打开，LED2关闭
{
   GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_15, SET);
	 GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_14, RESET);
	
}

void lightline_Init(void)
{
	CKCU_PeripClockConfig_TypeDef LEDClock = {{ 0 }};
	LEDClock.Bit.PC = 1; //使能PC
	CKCU_PeripClockConfig(LEDClock, ENABLE); //一定要先使能时钟，再配置下面的
	GPIO_DirectionConfig(HT_GPIOC, GPIO_PIN_2, GPIO_DIR_OUT); //设置PC15为输出
	GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_2, RESET);
}

void lightline_Check(void)
{
	if(LF==1)
	GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_2, SET);
	else if(LF==0)
	GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_2, RESET);
}

