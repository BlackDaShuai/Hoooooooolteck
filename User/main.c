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

unsigned short timeCount = 50; //发送间隔变量
unsigned char *dataPtr = NULL; //wifi数据

void HardwareInit(void);
void printfInfo(void);


int main(void)
{
	
	
	HardwareInit();//dht11init时会串口发送check，0为收到
	
	while (1)
	{
		timeCount ++;
		led_on();
		if(timeCount >= TIME) //定期获取信息
		{
			dht11_read_data(&temper,&humidity); //dht11获取温湿度数据
			DS18B20_GetTemp_MatchRom ( ucDs18b20Id ); //ds18b20获取温度
			
			ADC_Get();//获取ADC电压(用于TDS)
			transTDS();
			printfInfo();
			OneNet_SendData();
			ESP8266_Clear();
			timeCount = 0;
		}
		
		
		shipFunction();//小船行走标志位判断
		rollerFunction();//滚筒标志位判断
		lightline_Check();//灯带标志位判断
		
		dataPtr = ESP8266_GetIPD(3); //接收网络数据
		if(dataPtr != NULL) 
			OneNet_RevPro(dataPtr);

		led_off(); //系统运行状态指示灯
		delay_ms(30);
	}
	
}




void HardwareInit(void) //功能初始化
{

	delay_init();
	USART1_Configuration();				//串口1，打印信息用
	USART2_Configuration();				//串口2，驱动ESP8266用
	motorInit();

	led_init();
	lightline_Init();
	dht11_init();			//需要放在串口配置后

	ESP8266_Init();					//初始化ESP8266

	while(OneNet_DevLink())			//接入OneNET
	delay_ms(500);



	DS18B20_Init();
	ADC_Configuration();
	DS18B20_ReadId ( ucDs18b20Id  ); // 读取 DS18B20 的序列号
	printf(" Hardware init OK\r\n");
}




//串口0打印信息
void printfInfo(void)
{


	printf("Temperature:%d°C,Humidity:%d%%\r\n\n",temper,humidity); //输出温湿度数据

	printf("TempInWater:%.1f°C\r\n",temperds);
	
	printf("Turbidity:%dppm\r\n",TDS);
	
	printf("ActionFlag:%d\r\n",actionFlag);
	
	printf("RollerFlag:%d\r\n",rollerFlag);
	

}

