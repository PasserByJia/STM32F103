#ifndef  __TEST_H
#define	 __TEST_H



#include "stm32f10x.h"



/********************************** 用户需要设置的参数**********************************/
#define      macUser_ESP8266_ApSsid                       "jjj"                //要连接的热点的名称
#define      macUser_ESP8266_ApPwd                        "jh112358"           //要连接的热点的密钥

#define      macUser_ESP8266_TcpServer_IP                 "192.168.8.125"      //要连接的服务器的 IP192.168.8.125  39.108.216.189
#define      macUser_ESP8266_TcpServer_Port               "8081"               //要连接的服务器的端口
#define delay_ms 			mdelay


/********************************** 外部全局变量 ***************************************/
extern volatile uint8_t ucTcpClosedFlag;



/********************************** 测试函数声明 ***************************************/
void ESP8266_WebFetch_Test (char a[50]);
void HC_05_Init(char a[50]);



#endif



