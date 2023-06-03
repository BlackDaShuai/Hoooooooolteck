#include "ht32.h"
#include "pwm.h"
#include "motor.h"

void motorGPIOInit(void)
{
    CKCU_PeripClockConfig_TypeDef motorDrectionClock = {{ 0 }};
	motorDrectionClock.Bit.PB = 1; //使能PB
	CKCU_PeripClockConfig(motorDrectionClock, ENABLE); //
		
		    CKCU_PeripClockConfig_TypeDef STBYClock = {{ 0 }};
	STBYClock.Bit.PC = 1; //使能STBY
	CKCU_PeripClockConfig(STBYClock, ENABLE); //
		
	GPIO_DirectionConfig(HT_GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_10, GPIO_DIR_OUT); //设置PB0PB1PB2PB3为输出
	GPIO_DirectionConfig(HT_GPIOC,GPIO_PIN_1, GPIO_DIR_OUT); //设置PB10为输出

		//电机1正转
    GPIO_WriteOutBits(HT_GPIOB, GPIO_PIN_0, RESET);
	GPIO_WriteOutBits(HT_GPIOB, GPIO_PIN_1, SET);
    //电机2正转
    GPIO_WriteOutBits(HT_GPIOB, GPIO_PIN_2, RESET);
	GPIO_WriteOutBits(HT_GPIOB, GPIO_PIN_3, SET);

    //电机3正转(滚筒的电机)
//		  GPIO_SetOutBits         (OUT_PB10_GPIO_PORT, OUT_PB10_GPIO_PIN);
//  GPIO_DirectionConfig    (OUT_PB10_GPIO_PORT, OUT_PB10_GPIO_PIN, GPIO_DIR_OUT);
			GPIO_WriteOutBits(HT_GPIOC, GPIO_PIN_1, SET);//STBY使能

    GPIO_WriteOutBits(HT_GPIOB, GPIO_PIN_4, RESET);
	GPIO_WriteOutBits(HT_GPIOB, GPIO_PIN_5, SET);
}

void motorInit(void)
{
    motorGPIOInit();
    PWM_Init();
    PWM_UpdateDuty(PWM_CH0, PWM_DUTY_0);
  	PWM_UpdateDuty(PWM_CH1, PWM_DUTY_0);
    PWM_UpdateDuty(PWM_CH2, PWM_DUTY_0);
  	PWM_Cmd(ENABLE);

}

void shipLeft(void)
{
    PWM_UpdateDuty(PWM_CH0, PWM_DUTY_0);
    PWM_UpdateDuty(PWM_CH1, PWM_DUTY_100);
}

void shipRight(void)
{
    PWM_UpdateDuty(PWM_CH0, PWM_DUTY_100);
    PWM_UpdateDuty(PWM_CH1, PWM_DUTY_0);
}

void shipGoFast(void)
{
    PWM_UpdateDuty(PWM_CH0, PWM_DUTY_100);
    PWM_UpdateDuty(PWM_CH1, PWM_DUTY_100);
}

void shipGoSlow(void)
{
    PWM_UpdateDuty(PWM_CH0, PWM_DUTY_75);
    PWM_UpdateDuty(PWM_CH1, PWM_DUTY_75);
}


void shipStop(void)
{
    PWM_UpdateDuty(PWM_CH0, PWM_DUTY_0);
    PWM_UpdateDuty(PWM_CH1, PWM_DUTY_0);
}

void shipBack(void)
{
	  PWM_UpdateDuty(PWM_CH0, PWM_DUTY_0);
    PWM_UpdateDuty(PWM_CH1, PWM_DUTY_0);
		//电机1反转
    GPIO_WriteOutBits(HT_GPIOB, GPIO_PIN_0, SET);
	GPIO_WriteOutBits(HT_GPIOB, GPIO_PIN_1, RESET);
    //电机2反转
    GPIO_WriteOutBits(HT_GPIOB, GPIO_PIN_2, SET);
	GPIO_WriteOutBits(HT_GPIOB, GPIO_PIN_3, RESET);
		PWM_UpdateDuty(PWM_CH0, PWM_DUTY_75);
    PWM_UpdateDuty(PWM_CH1, PWM_DUTY_75);
	
	
}

void RollerOn(void)
{
    PWM_UpdateDuty(PWM_CH2, PWM_DUTY_50);
}

void RollerOff(void)
{
    PWM_UpdateDuty(PWM_CH2, PWM_DUTY_0);
}

void shipFunction(void)
{
	if(actionFlag == 0)
		{
			shipStop();
		}
		else if(actionFlag == 1)
		{
			shipGoSlow();
		}
		else if(actionFlag == 2)
		{
			shipGoFast();
		}
		else if(actionFlag == 3)
		{
			shipLeft();
		}
		else if(actionFlag == 4)
		{
			shipRight();
		}
		else if(actionFlag == 5)
		{
			shipBack();
		}
//		else{shipStop();}
	
}

void rollerFunction(void)
{
	if(rollerFlag == 0)RollerOff();
	else if(rollerFlag == 1)RollerOn();
	else{RollerOff();}
}

