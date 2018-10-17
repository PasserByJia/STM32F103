char* redata;
		char cStr [ 100 ] = { 0 };
	uint16_t len;
	static uint8_t hc05_role=1;
	unsigned long count;
	
	char hc05_mode[10]="SLAVE";
	char hc05_name[30]="HC05_SLAVE";
	char hc05_nameCMD[40];
	char str[20];
	
	  //��ʼ��systick
	SysTick_Init();
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;

	USART_Config();
	
	ESP8266_Init (); 
	HC05_INFO("**********HC05ģ��ʵ��************");
	
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
	
	HC05_Send_CMD("AT+VERSION?\r\n",1);
	
	HC05_Send_CMD("AT+ADDR?\r\n",1);
	
	HC05_Send_CMD("AT+UART?\r\n",1);
	
	HC05_Send_CMD("AT+CMODE?\r\n",1);
	
	HC05_Send_CMD("AT+STATE?\r\n",1);	

	HC05_Send_CMD("AT+ROLE=1\r\n",1);
	
	/*��ʼ��SPP�淶*/
	HC05_Send_CMD("AT+INIT\r\n",1);
	HC05_Send_CMD("AT+CLASS=0\r\n",1);
	HC05_Send_CMD("AT+INQM=1,9,48\r\n",1);
	
	/*����ģ������*/
	//sprintf(hc05_nameCMD,"AT+NAME=%s\r\n",hc05_name);
	//HC05_Send_CMD(hc05_nameCMD,1);

	HC05_INFO("��ģ������Ϊ:%s ,ģ����׼��������",hc05_name);

	while(1)
	{

		//��������ģ�飬����������
		if(Task_Delay[2]==0 && !IS_HC05_CONNECTED()) 
		{
			if(hc05_role == 1)	//��ģʽ AT+STATE?
			{
				HC05_INFO("����ɨ�������豸...");
				linkHC05();
				Task_Delay[2]=3000; //��ֵÿ1ms���1������0�ſ������½����������ִ�е�������3s
			}
		}				
		
			//���Ӻ�ÿ��һ��ʱ������ջ�����
		if(Task_Delay[0]==0 && IS_HC05_CONNECTED())  
		{
				uint16_t linelen;

				/*��ȡ����*/
				redata = get_rebuff(&len); 
				linelen = get_line(linebuff,redata,len);
			
				/*��������Ƿ��и���*/
				if(linelen<200 && linelen != 0)
				{
					 
					sprintf ( cStr,redata);
		
					ESP8266_SendString ( ENABLE, cStr, 0, Single_ID_0 );               //��������
					
					delay_ms ( 100 );
						//HC05_INFO("receive:\r\n%s",redata);
					/*�������ݺ���ս�������ģ�����ݵĻ�����*/
					clean_rebuff();
					
				}
			Task_Delay[0]=500;//��ֵÿ1ms���1������0�ſ������½����������ִ�е�������500ms
		}
	}
	
	/*ESP8266_Init ();                                                               //��ʼ��WiFiģ��ʹ�õĽӿں�����

	
	printf ( "\r\nҰ�� WF-ESP8266 WiFiģ���������\r\n" );                          //��ӡ����������ʾ��Ϣ

	
  ESP8266_StaTcpClient_UnvarnishTest ();
	
	
  while ( 1 );*
  =============
  void ESP8266_WebFetch_Test ( void )
{
	char cStrInput [100] = { 0 }, * pStrDelimiter [2], * pBuf, * pStr;
	u8 uc = 0;


  printf( "\r\n�������Է��ʡ�eat.weixincore.com/index.php?s=/Mobile/PrinterTest/index��Ϊ��\r\n" );
  delay_ms ( 3000 );


	ESP8266_Choose ( ENABLE );	


	ESP8266_AT_Test ();
	

	ESP8266_Net_Mode_Choose ( STA );
  

	ESP8266_Cmd ( "AT+CWLAP", "OK", 0, 5000 );

	/*
		��������
	*/
while ( ! ESP8266_JoinAP ( macUser_ESP8266_ApSsid, macUser_ESP8266_ApPwd ) );

ESP8266_Enable_MultipleId ( DISABLE );
	
while ( !	ESP8266_Link_Server ( enumTCP, macUser_ESP8266_TcpServer_IP, macUser_ESP8266_TcpServer_Port, Single_ID_0 ) );
	
	
	ESP8266_UnvarnishSend ();
	
	ESP8266_SendString ( ENABLE, "GET /getUrlController?id=666 HTTP/1.1\r\n", NULL, Single_ID_0 );
	ESP8266_SendString ( ENABLE, "Host: 192.168.8.101\r\n",                            NULL, Single_ID_0 );
	ESP8266_SendString ( ENABLE, "User-Agent: abc\r\n",                                     NULL, Single_ID_0 );
	ESP8266_SendString ( ENABLE, "Connection: close\r\n",                                   NULL, Single_ID_0 );
	ESP8266_SendString ( ENABLE, "\r\n",                                                    NULL, Single_ID_0 );
	

	USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);
	

}