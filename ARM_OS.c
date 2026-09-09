
#include <string.h>
#include <stdio.h>
#include <Net_Config.h>
#include "APP\EXTERNALS.h"
#include <RTL.h>

extern U16 cgi_process_meteo(U8 *buf, const char *env, const char *input);
extern U16 cgi_process_index(U8 *buf, const char *env, const char *input);
//extern U16 cgi_process_data(U8 *buf, const char *env, const char *input);



extern U8 spisok[8][6];
 BOOL DATCHIK = __FALSE;
BOOL HIDER = __FALSE;
 
U8 spisok_dav[11] = {0xAA, 0x55, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
U8 spisok_temp[11] = {0xAA, 0x55, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
U8 spisok_vlaga[11] = {0xAA, 0x55, 0x01, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03};
U8 spisok_napravlenieVetra[11] = {0xAA, 0x55, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02};
U8 spisok_skorost[11] = {0xAA, 0x55, 0x01, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05};
U8 *spisok_parametr= NULL;


float davlenie = 0.0f;
float temperatura = 29.0f;
float vlaga = 0.0f;
float napravlenieVetra = 0.0f;
float skorost = 0.0f;

// TCP server functions for LabVIEW communication
#define TCP_SERVER_PORT  8080
#define MAX_TCP_CLIENTS  1
#define TCP_BUFFER_SIZE  256

static TCP_INFO tcp_server[MAX_TCP_CLIENTS];
static U8 tcp_server_active = 0;
static U8 tcp_send_buffer[TCP_BUFFER_SIZE];
static U8 tcp_recv_buffer[TCP_BUFFER_SIZE];

U16 tcp_server_callback(U8 socket, U8 event, U8 *p1, U16 p2) {
    U16 len;
    
    switch (event) {
        case TCP_EVT_CONNECT:
            printf("TCP Client connected on socket %d\n", socket);
            tcp_server_active = 1;
            break;
        case TCP_EVT_CLOSE:
            printf("TCP Client disconnected from socket %d\n", socket);
            tcp_server_active = 0;
            break;
        case TCP_EVT_ACK:
            break;
        case TCP_EVT_DATA:
            len = p2;
            if (len > 0) {
                printf("Received %d bytes from LabVIEW\n", len);
                if (len < TCP_BUFFER_SIZE) {
                    memcpy(tcp_send_buffer, p1, len);  // p1 points to received data
                    // Echo back received data
                    for (U8 i = 0; i < MAX_TCP_CLIENTS; i++) {
                        if (tcp_server[i].State == 11) {  // TCP_STATE_CONNECTED = 11
                            tcp_send(i, tcp_send_buffer, len);
                            break;
                        }
                    }
                }
            }
            break;
    }
    return 0;
}

void init_tcp_server(void) {
    U8 i;
    
    printf("Initializing TCP Server on port %d...\n", TCP_SERVER_PORT);
    
    // Initialize TCP sockets - using correct structure fields
    for (i = 0; i < MAX_TCP_CLIENTS; i++) {
        tcp_server[i].State = 1;  // TCP_STATE_CLOSED = 1
        tcp_server[i].cb_func = tcp_server_callback;
    }
    
    // Start listening for incoming connections - using correct parameters
    if (tcp_listen(0, TCP_SERVER_PORT) == 0) {
        printf("TCP Server started successfully\n");
        tcp_server_active = 1;
    } else {
        printf("Failed to start TCP Server\n");
        tcp_server_active = 0;
    }
}

void process_tcp_server(void) {
    if (tcp_server_active) {
        tcp_poll_sockets();
        
        U16 len;
        
        len = sprintf((char*)tcp_send_buffer, 
                      "Temperature: %.2f,Pressure: %.2f,Humidity: %.2f,WindSpeed: %.2f,WindDir: %.2f\n",
                      temperatura, davlenie, vlaga, skorost, napravlenieVetra);
        
        // Find active socket and send data
        for (U8 i = 0; i < MAX_TCP_CLIENTS; i++) {
            if (tcp_server[i].State == 11) {  // TCP_STATE_CONNECTED = 11
                if (tcp_send(i, tcp_send_buffer, len) == 0) {
                    printf("Sent meteo data to LabVIEW\n");
                }
                break;
            }
        }
    }
}

// создадим функицю таймера(чтобы была зедержка между отправленными и принятыми данными)
void delay_ms(unsigned int ms)
{
	volatile unsigned int i, j;
	for (int i = 0; i< ms; i++)
	{
		for(int j = 0; j< 5000; j++)
		{
		}
	}
}


//---------------------------
// MAIN
//---------------------------
int main (void) {
int current_parametr = 0;
// буфер для принятия данных с метеостанции
 static U8 rx_buff[11];
// индекс  принятого байта
 static U8 rx_index;
// проверка успешно ли произошло принятие данных с метеостанции
 BOOL rx_compete = __FALSE;
 // проверка того какой именно параметр передала нам метеостанция 
 U8 parametr_type;
// типы параметров для извлечения данных

	U8 arrays[5][11];
// масавсив из массивов ответов для одновременного вывода всех параметов раз в секунду 
Init_Dev     ();
	int schetchik = 0; // чтобы считать номер принятого массива и записывать в массив массивов 
	
	
// списки для отправки запрос по разным величинам  

//get_button_1 ();




init_TcpNet ();



//  DHCP configuration
  dhcp_disable();
 
finit ("M");
 
// Initialize TCP server for LabVIEW communication
init_tcp_server();    


	 DATCHIK = __FALSE;
	 HIDER = __FALSE;
	 
	 Temperatura = 29.0f;
	 
	 clb_time = 11;
	
while (1)
  {
		main_TcpNet();
		Timer_Poll();
		RTC_Poll();
		
		// Process TCP server for LabVIEW communication
		process_tcp_server();

	
	
		

// =============================== отправка данных=================================
// PPS выставялется в RTC_POLL раз в секунду, если он стоит выбираем следующий запрос 
// затем отправляем 11 байт 
//SETBIT(flag1, PPS);
if (CHECKBIT(flag1, PPS))
{
	switch(current_parametr)
	{
		case 0:
			spisok_parametr = spisok_dav; break;
		case 1:
			spisok_parametr = spisok_temp; break;
		case 2:
			spisok_parametr = spisok_vlaga; break;
		case 3: 
			spisok_parametr = spisok_napravlenieVetra; break;
		case 4:
			spisok_parametr = spisok_skorost; break;
		default:
			current_parametr = 0;
		  spisok_parametr = spisok_dav;
	   	break;
	}
	
	check_up_flags(); // реальная отправка 11 байт
	current_parametr++;
	if (current_parametr >=5)
	{
    current_parametr =0;
  }
	
}
else
	{
	check_up_flags();
}

delay_ms(200);

		// ========================= прием данных===============================
while (U1LSR & 0x01) // в регистре есть данные
{ 
	U8 byte;
	byte = U1RBR;
	
	  if (rx_index == 0)
		{
			if (byte != 0xAA)
			{
				continue; // значит что передается мусор следовательбно ждем начало следующего пакета
			}
			 rx_buff[rx_index] = byte;
			rx_index++;
			continue;
		}
		// ждем второй байт заголовка
		if (rx_index == 1)
		{
			if (byte != 0x55)
			{
				rx_index = 0; // заголовок неверный следовательно начинаем заново 
				continue;
			}
			rx_buff[rx_index] = byte;
			rx_index++;
			continue;
		}
		
		// остальные байты пакета 
		rx_buff[rx_index] = byte;
		rx_index++;

if (rx_index >=11)
{
	rx_compete = __TRUE;
	rx_index = 0;
	break; // пакет ответа собран обработка будет потом 
}
	
		
}


if(rx_compete == __TRUE) // если мы приняли весь пакет байт 
{
	rx_compete = __FALSE;
	if ((rx_buff[0] == 0xAA) && (rx_buff[1] == 0x55))
	{
	parametr_type = rx_buff[4]; // уточняем какие именно данные тут получили(давление температуры и так далее)
	 schetchik +=1;
		for (int j = 0; j < 11; j++)
		{
			arrays[schetchik][j] = rx_buff[j];
		}
	
		// если мы приняли и записали все данные всех парметров в массив arrays то реализуем "вывод"
if (schetchik == 4)
{
	  memcpy(&davlenie, &arrays[0][5], 4);/* printf("%.2f\r\n", davlenie);*/
	  memcpy(&temperatura, &arrays[1][5], 4);
	  memcpy(&vlaga, &arrays[2][5], 4);
	  memcpy(&napravlenieVetra, &arrays[3][5], 4);
	  memcpy(&skorost, &arrays[4][5], 4);
}
// обнуление счетчика для нового "сбора" данных
 if((schetchik >= 4))
	{
		schetchik = 0;
		for (int i = 0; i < 5; i++)
		{
		for (int j = 0; j < 11; j++)
		{
			arrays[i][j] = 0;
		}
	}
	}
 }
}


}
	}

	
	
	
	
	
	// для одновременного вывода всех данных сделал
	/*
	 1) сделал массив с массивами данных двумерный и счетчик чтобы записывать массив каждого параметра в отдельную ячейку
	2) вместо выводу свитч кейс сделал прямой вывод прямо из массива массивов 
	3) сделал цикл для очистки массива массивов и соответственно самого счетчика тоже 
	*/