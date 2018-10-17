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
	//�����������ݽ���
	char* redata;
	//�������ü���
	int count =0;
	int flag =0;
	//�������ݳ���
	uint16_t len;
	uint16_t getlen=0;
	uint8_t linenum=0;	

	//��ʼ��systick
	SysTick_Init();
	//�����δ�ʱ��
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;

	//��ʼ������ͨ�Ŵ���
	USART_Config();
	
  BLT_USART_Config();
	
	ESP8266_Init ();

	while(1)
	{	
			//���Ӻ�ÿ��һ��ʱ������ջ�����
		if(Task_Delay[0]==0 )
		{
				uint16_t linelen;
				//flag=1;
				/*��ȡ����*/
				redata = get_rebuff(&len); 

				linelen = get_line(linebuff,redata,len);
				/*��������Ƿ��и���*/
				if(linelen != 0 && linelen>=25)
				{
					printf("%s\n",linebuff);
					memset(cStr, 0, sizeof(cStr));
					strcat(cStr,"GET /update");
					strcat(cStr,linebuff);
					strcat(cStr," HTTP/1.1\r\n");
					//printf("%s\n",cStr);
					ESP8266_WebFetch_Test(cStr);
					/*�������ݺ���ս�������ģ�����ݵĻ�����*/
					clean_rebuff();
				}

			Task_Delay[0]=300;//��ֵÿ1ms���1������0�ſ������½����������ִ�е�������500ms
		}
	}
}



