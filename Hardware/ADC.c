#include "ADC.h"

//-----------------------------------------------------------------------------
vu8 adc_result_update;
vu16 adc_result[14];

//-----------------------------------------------------------------------------
void ADC_Configuration(void)
{
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
  CKCUClock.Bit.ADC   = 1;
  CKCUClock.Bit.AFIO  = 1;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);

  ADC_Reset(HT_ADC);
  CKCU_SetADCPrescaler(CKCU_ADCPRE_DIV16);    //使能ADC时钟为16分频

  AFIO_GPxConfig(GPIO_PA, AFIO_PIN_0, AFIO_FUN_ADC);  //复用引脚为ADC

  ADC_RegularChannelConfig(HT_ADC, ADC_CH_0, 0); //设置为规则通道0


  ADC_RegularGroupConfig(HT_ADC, CONTINUOUS_MODE, 1, 1);  //设置为连续转换
  ADC_RegularTrigConfig(HT_ADC, ADC_TRIG_SOFTWARE);     //设置为软件触发
  ADC_SamplingTimeConfig(HT_ADC, 2); //设置转换时间为2(0-255)
//  ADC_IntConfig(HT_ADC, ADC_INT_CYCLE_EOC, ENABLE); //使能ADC中断
  ADC_Cmd(HT_ADC, ENABLE);
  NVIC_EnableIRQ(ADC_IRQn);
  ADC_SoftwareStartConvCmd(HT_ADC, ENABLE);   //使能外部调用
}


//-----------------------------------------------------------------------------
void ADC_IRQHandler(void)
{
  if(ADC_GetIntStatus(HT_ADC, ADC_INT_CYCLE_EOC))
  {
    ADC_ClearIntPendingBit(HT_ADC, ADC_FLAG_CYCLE_EOC);
    adc_result[0] = HT_ADC->DR[0];
    adc_result_update = 1;
    //ADC_SoftwareStartConvCmd(HT_ADC, ENABLE);   // Trigger to NEXT start?
  }
}

void ADC_Get(void)
{

			adc_result[0] = HT_ADC->DR[0];
			adc_result_update = 1;
//			ADC_SoftwareStartConvCmd(HT_ADC, ENABLE);
}
//-----------------------------------------------------------------------------


