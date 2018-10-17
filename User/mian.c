#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./usart/bsp_usart_blt.h"
#include "./SysTick/bsp_SysTick.h"
#include "./hc05/bsp_hc05.h"
#include "bsp_esp8266.h"
#include "test.h"
#include "bsp_led.h"
#include <string.h>
#include <stdlib.h>


unsigned int Task_Delay[3]; 


BLTDev bltDevList;




char sendData[1024];
char linebuff[1024];


int main(void)
{
	char cStr [ 1500 ];
	//蓝牙缓存数据接收
	char* redata;
	//蓝牙重置计数
	int count =0;
	int flag =0;
	//缓存数据长度
	uint16_t len;
	uint16_t getlen=0;
	uint8_t linenum=0;	

	//初始化systick
	SysTick_Init();
	//开启滴答定时器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;

	//初始化电脑通信串口
	USART_Config();
	
  BLT_USART_Config();
	
	ESP8266_Init ();

	while(1)
	{	
			//连接后每隔一段时间检查接收缓冲区
		if(Task_Delay[0]==0 )
		{
				uint16_t linelen;
				//flag=1;
				/*获取数据*/
				redata = get_rebuff(&len); 

				linelen = get_line(linebuff,redata,len);
				/*检查数据是否有更新*/
				if(linelen != 0 && linelen>=25)
				{
					printf("%s\n",linebuff);
					memset(cStr, 0, sizeof(cStr));
					strcat(cStr,"GET /update");
					strcat(cStr,linebuff);
					strcat(cStr," HTTP/1.1\r\n");
					//printf("%s\n",cStr);
					ESP8266_WebFetch_Test(cStr);
					/*处理数据后，清空接收蓝牙模块数据的缓冲区*/
					clean_rebuff();
				}

			Task_Delay[0]=300;//此值每1ms会减1，减到0才可以重新进来这里，所以执行的周期是500ms
		}
	}
}



