#ifndef _ONENET_H_
#define _ONENET_H_





_Bool OneNet_DevLink(void); //与onenet创建连接

void OneNet_SendData(void);
void OneNet_SendCmd(void);
void OneNet_RevPro(unsigned char *cmd);

#endif
