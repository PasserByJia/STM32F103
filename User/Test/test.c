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
 * ��������ESP8266_WebFetch_Test
 * ����  ��WF-ESP8266ģ�����http���Ӳ���
 * ����  ����
 * ����  : ��
 * ����  �����ⲿ����
 */
void ESP8266_WebFetch_Test (char a[50])
{
	uint8_t ucStatus;
	int count1=0;
	int count2=0;
	int count3=0;
	//��Զ�̷���������TCP����
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
	//����͸��ģʽ
	//ESP8266_Get_LinkStatus();
	//while ( ! ESP8266_UnvarnishSend () && count2<4) count2++;
	//����httpЭ�鴫��
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
		HC05_INFO("HC05ģ����������");
	else
	{
		HC05_ERROR("HC05ģ���ⲻ����������ģ���뿪��������ӣ�Ȼ��λ���������²��ԡ�");
		while(1);
	}


	/*��λ���ָ�Ĭ��״̬*/
	HC05_Send_CMD("AT+RESET\r\n",1);	
	delay_ms(800);
	
	HC05_Send_CMD("AT+ORGL\r\n",1);
	delay_ms(200);

	
	/*�������������ʾ��Ĭ�ϲ���ʾ��
	 *��bsp_hc05.h�ļ���HC05_DEBUG_ON ������Ϊ1��
	 *����ͨ�����ڵ������ֽ��յ�����Ϣ*/	
	
//	HC05_Send_CMD("AT+VERSION?\r\n",1);
	
//	HC05_Send_CMD("AT+ADDR?\r\n",1);
	
//	HC05_Send_CMD("AT+UART?\r\n",1);
	
//	HC05_Send_CMD("AT+CMODE?\r\n",1);
	
//	HC05_Send_CMD("AT+STATE?\r\n",1);	

	HC05_Send_CMD("AT+ROLE=1\r\n",1);
	
	/*��ʼ��SPP�淶*/
	HC05_Send_CMD("AT+INIT\r\n",1);
	HC05_Send_CMD("AT+CLASS=0\r\n",1);
	HC05_Send_CMD("AT+INQM=1,9,48\r\n",1);
	
	/*����ģ������*/
	//sprintf(hc05_nameCMD,"AT+NAME=%s\r\n",hc05_name);
	//HC05_Send_CMD(hc05_nameCMD,1);

	HC05_INFO("��ģ������Ϊ:%s ,ģ����׼��������",a);
}


