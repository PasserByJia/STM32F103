#include "test.h"
#include "./hc05/bsp_hc05.h"
#include "bsp_esp8266.h"
#include "bsp_SysTick.h"
#include <stdio.h>  
#include <string.h>  
#include <stdbool.h>



volatile uint8_t ucTcpClosedFlag = 0;

char cStr [ 1500 ];



/*
 * 函数名：ESP8266_WebFetch_Test
 * 描述  ：WF-ESP8266模块进行http连接测试
 * 输入  ：无
 * 返回  : 无
 * 调用  ：被外部调用
 */
void ESP8266_WebFetch_Test (char a[50])
{
	uint8_t ucStatus;
	int count1=0;
	int count2=0;
	int count3=0;
	//与远程服务器进行TCP连接
	//if()printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n");
	if(ESP8266_Get_LinkStatus()==4)
	{
		//printf("==================");
		ESP8266_Cmd("AT+CIPCLOSE\r\n","OK", 0, 500);
		ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 );
		ESP8266_UnvarnishSend ();
	}else
	{
		ESP8266_UnvarnishSend ();
	}
	//while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) && count1<10) count1++;
	//进入透传模式
	//ESP8266_Get_LinkStatus();
	//while ( ! ESP8266_UnvarnishSend () && count2<4) count2++;
	//进行http协议传输
	ESP8266_SendString ( ENABLE, a, NULL, Single_ID_0 );
	ESP8266_SendString ( ENABLE, "Host: 192.168.8.125:8081\r\n",                            NULL, Single_ID_0 );
	ESP8266_SendString ( ENABLE, "User-Agent: abc\r\n",                                     NULL, Single_ID_0 );
	ESP8266_SendString ( ENABLE, "Connection: Keep Alive\r\n",                                   NULL, Single_ID_0 );
	ESP8266_SendString ( ENABLE, "\r\n",                                                    NULL, Single_ID_0 );
	
	ESP8266_ExitUnvarnishSend ();
	
	//while ( !	ESP8266_Cmd("AT+CIPCLOSE\r\n","OK", 0, 500) && count3<10 ) count3++;
	
}

void HC_05_Init(char a[50])
{
		if(HC05_Init() == 0)
		HC05_INFO("HC05模块检测正常。");
	else
	{
		HC05_ERROR("HC05模块检测不正常，请检查模块与开发板的连接，然后复位开发板重新测试。");
		while(1);
	}


	/*复位、恢复默认状态*/
	HC05_Send_CMD("AT+RESET\r\n",1);	
	delay_ms(800);
	
	HC05_Send_CMD("AT+ORGL\r\n",1);
	delay_ms(200);

	
	/*各种命令测试演示，默认不显示。
	 *在bsp_hc05.h文件把HC05_DEBUG_ON 宏设置为1，
	 *即可通过串口调试助手接收调试信息*/	
	
//	HC05_Send_CMD("AT+VERSION?\r\n",1);
	
//	HC05_Send_CMD("AT+ADDR?\r\n",1);
	
//	HC05_Send_CMD("AT+UART?\r\n",1);
	
//	HC05_Send_CMD("AT+CMODE?\r\n",1);
	
//	HC05_Send_CMD("AT+STATE?\r\n",1);	

	HC05_Send_CMD("AT+ROLE=1\r\n",1);
	
	/*初始化SPP规范*/
	HC05_Send_CMD("AT+INIT\r\n",1);
	HC05_Send_CMD("AT+CLASS=0\r\n",1);
	HC05_Send_CMD("AT+INQM=1,9,48\r\n",1);
	
	/*设置模块名字*/
	//sprintf(hc05_nameCMD,"AT+NAME=%s\r\n",hc05_name);
	//HC05_Send_CMD(hc05_nameCMD,1);

	HC05_INFO("本模块名字为:%s ,模块已准备就绪。",a);
}


