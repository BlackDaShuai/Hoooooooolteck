#include "ht32.h"
#include "ht32_board.h"
#include "ht32_board_config.h"
#include "usart.h"
#include "delay.h"
#include "dht11.h"
#include "led.h"
#include "ds18b20.h"
#include "ADC.h"
#include "tds.h"
#include "pwm.h"
#include "motor.h"
#include "esp8266.h"
#include "onenet.h"
#include "MqttKit.h"
#include "string.h"
#define TIME 100


unsigned char temper = 0,humidity = 0;
int TDS = 0;
float TDSvoltage = 0.0;
float temperds = 0.0;
char string1[3] = {0};
int actionFlag = 0;
int rollerFlag = 0;
int LF = 0;
uint8_t ucDs18b20Id [ 8 ];

unsigned short timeCount = 50; //���ͼ������
unsigned char *dataPtr = NULL; //wifi����

void HardwareInit(void);
void printfInfo(void);


int main(void)
{
	
	
	HardwareInit();//dht11initʱ�ᴮ�ڷ���check��0Ϊ�յ�
	
	while (1)
	{
		timeCount ++;
		led_on();
		if(timeCount >= TIME) //���ڻ�ȡ��Ϣ
		{
			dht11_read_data(&temper,&humidity); //dht11��ȡ��ʪ������
			DS18B20_GetTemp_MatchRom ( ucDs18b20Id ); //ds18b20��ȡ�¶�
			
			ADC_Get();//��ȡADC��ѹ(����TDS)
			transTDS();
			printfInfo();
			OneNet_SendData();
			ESP8266_Clear();
			timeCount = 0;
		}
		
		
		shipFunction();//С�����߱�־λ�ж�
		rollerFunction();//��Ͳ��־λ�ж�
		lightline_Check();//�ƴ���־λ�ж�
		
		dataPtr = ESP8266_GetIPD(3); //������������
		if(dataPtr != NULL) 
			OneNet_RevPro(dataPtr);

		led_off(); //ϵͳ����״ָ̬ʾ��
		delay_ms(30);
	}
	
}




void HardwareInit(void) //���ܳ�ʼ��
{

	delay_init();
	USART1_Configuration();				//����1����ӡ��Ϣ��
	USART2_Configuration();				//����2������ESP8266��
	motorInit();

	led_init();
	lightline_Init();
	dht11_init();			//��Ҫ���ڴ������ú�

	ESP8266_Init();					//��ʼ��ESP8266

	while(OneNet_DevLink())			//����OneNET
	delay_ms(500);



	DS18B20_Init();
	ADC_Configuration();
	DS18B20_ReadId ( ucDs18b20Id  ); // ��ȡ DS18B20 �����к�
	printf(" Hardware init OK\r\n");
}




//����0��ӡ��Ϣ
void printfInfo(void)
{


	printf("Temperature:%d��C,Humidity:%d%%\r\n\n",temper,humidity); //�����ʪ������

	printf("TempInWater:%.1f��C\r\n",temperds);
	
	printf("Turbidity:%dppm\r\n",TDS);
	
	printf("ActionFlag:%d\r\n",actionFlag);
	
	printf("RollerFlag:%d\r\n",rollerFlag);
	

}

