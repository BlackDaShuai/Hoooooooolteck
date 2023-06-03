#include "tds.h"
#include "ADC.h"
#include "ds18b20.h"


float Tfix = 0.0,TDSfix=0.0,PPMvalue=0.0;

//TDSֵת������
float transTDS(void)
{
  TDSvoltage = (adc_result[0]/4096.0)*3.3; //����ѹ��ʾ����
//	printf("vol=%f\r\n",TDSvoltage);
	Tfix = 1.0 + 0.02 * (temperds-25.0); //�����¶Ȳ���
	TDSfix = Tfix * TDSvoltage; //�����¶Ȳ�����ĵ�ѹ
	PPMvalue= (66.71*TDSfix*TDSfix*TDSfix)-(127.93*TDSfix*TDSfix)+(428.7*TDSfix); //����NTUֵ
	
	TDS = (int)PPMvalue;
	return PPMvalue;
}
