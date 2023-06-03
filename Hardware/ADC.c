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
  CKCU_SetADCPrescaler(CKCU_ADCPRE_DIV16);    //ʹ��ADCʱ��Ϊ16��Ƶ

  AFIO_GPxConfig(GPIO_PA, AFIO_PIN_0, AFIO_FUN_ADC);  //��������ΪADC

  ADC_RegularChannelConfig(HT_ADC, ADC_CH_0, 0); //����Ϊ����ͨ��0


  ADC_RegularGroupConfig(HT_ADC, CONTINUOUS_MODE, 1, 1);  //����Ϊ����ת��
  ADC_RegularTrigConfig(HT_ADC, ADC_TRIG_SOFTWARE);     //����Ϊ�������
  ADC_SamplingTimeConfig(HT_ADC, 2); //����ת��ʱ��Ϊ2(0-255)
//  ADC_IntConfig(HT_ADC, ADC_INT_CYCLE_EOC, ENABLE); //ʹ��ADC�ж�
  ADC_Cmd(HT_ADC, ENABLE);
  NVIC_EnableIRQ(ADC_IRQn);
  ADC_SoftwareStartConvCmd(HT_ADC, ENABLE);   //ʹ���ⲿ����
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


