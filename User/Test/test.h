#ifndef  __TEST_H
#define	 __TEST_H



#include "stm32f10x.h"



/********************************** �û���Ҫ���õĲ���**********************************/
#define      macUser_ESP8266_ApSsid                       "jjj"                //Ҫ���ӵ��ȵ������
#define      macUser_ESP8266_ApPwd                        "jh112358"           //Ҫ���ӵ��ȵ����Կ

#define      macUser_ESP8266_TcpServer_IP                 "192.168.8.125"      //Ҫ���ӵķ������� IP192.168.8.125  39.108.216.189
#define      macUser_ESP8266_TcpServer_Port               "8081"               //Ҫ���ӵķ������Ķ˿�
#define delay_ms 			mdelay


/********************************** �ⲿȫ�ֱ��� ***************************************/
extern volatile uint8_t ucTcpClosedFlag;



/********************************** ���Ժ������� ***************************************/
void ESP8266_WebFetch_Test (char a[50]);
void HC_05_Init(char a[50]);



#endif



