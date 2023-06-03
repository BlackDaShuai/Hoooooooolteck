#ifndef __DS18B20_H
#define	__DS18B20_H



#include "ht32.h"



/************************** DS18B20 连接引脚定义********************************/
#define      DS18B20_DQ_SCK_APBxClock_FUN              RCC_APB2PeriphClockCmd
#define      DS18B20_DQ_GPIO_CLK                       RCC_APB2Periph_GPIOE

#define      DS18B20_DQ_GPIO_PORT                      HT_GPIOB
#define      DS18B20_DQ_GPIO_PIN                       GPIO_PIN_6



/************************** DS18B20 函数宏定义********************************/
#define      DS18B20_DQ_0	                            GPIO_WriteOutBits(DS18B20_DQ_GPIO_PORT,DS18B20_DQ_GPIO_PIN,RESET)
#define      DS18B20_DQ_1	                            GPIO_WriteOutBits(DS18B20_DQ_GPIO_PORT,DS18B20_DQ_GPIO_PIN,SET)

#define      DS18B20_DQ_IN()	                        GPIO_ReadInBit(DS18B20_DQ_GPIO_PORT, DS18B20_DQ_GPIO_PIN) 



/************************** DS18B20 函数声明 ********************************/
uint8_t                  DS18B20_Init                      ( void );
void                     DS18B20_ReadId                    ( uint8_t * ds18b20_id );
float                    DS18B20_GetTemp_SkipRom           ( void );
float                    DS18B20_GetTemp_MatchRom          ( uint8_t * ds18b20_id );



extern float temperds;
extern char string1[3];






#endif /* __DS18B20_H */
