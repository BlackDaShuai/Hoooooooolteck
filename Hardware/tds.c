#include "tds.h"
#include "ADC.h"
#include "ds18b20.h"


float Tfix = 0.0,TDSfix=0.0,PPMvalue=0.0;

//TDS值转换函数
float transTDS(void)
{
  TDSvoltage = (adc_result[0]/4096.0)*3.3; //将电压表示出来
//	printf("vol=%f\r\n",TDSvoltage);
	Tfix = 1.0 + 0.02 * (temperds-25.0); //计算温度补偿
	TDSfix = Tfix * TDSvoltage; //计算温度补偿后的电压
	PPMvalue= (66.71*TDSfix*TDSfix*TDSfix)-(127.93*TDSfix*TDSfix)+(428.7*TDSfix); //计算NTU值
	
	TDS = (int)PPMvalue;
	return PPMvalue;
}
