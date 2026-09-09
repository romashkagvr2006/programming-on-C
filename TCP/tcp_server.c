/*----------------------------------------------------------------------------
 *      TCP Server for LabVIEW Communication
 *---------------------------------------------------------------------------*/

#include <Net_Config.h>
#include "APP\EXTERNALS.h"

#define TCP_SERVER_PORT  8080    // Port for LabVIEW communication
#define MAX_TCP_CLIENTS  1       // Maximum number of simultaneous LabVIEW connections

// TCP socket structure
static TCP_INFO tcp_server[MAX_TCP_CLIENTS];
static U8 tcp_server_active = 0;

// Buffer for sending data to LabVIEW
#define TCP_BUFFER_SIZE  256
static U8 tcp_send_buffer[TCP_BUFFER_SIZE];
static U8 tcp_recv_buffer[TCP_BUFFER_SIZE];

// Callback function for TCP socket events
U16 tcp_server_callback(U8 socket, U8 event, U8 *p1, U16 p2) {
    U16 len;
    
    switch (event) {
        case TCP_EVT_CONNECT:  // Client connected
            printf("TCP Client connected on socket %d\n", socket);
            break;
            
        case TCP_EVT_CLOSE:    // Client disconnected
            printf("TCP Client disconnected from socket %d\n", socket);
            tcp_server_active = 0;
            break;
            
        case TCP_EVT_ACK:      // Data acknowledged
            // Data was successfully sent to client
            break;
            
        case TCP_EVT_DATA:     // Data received from client
            len = p2;  // Length of received data
            if (len > 0) {
                // Process received data from LabVIEW
                printf("Received %d bytes from LabVIEW\n", len);
                
                // Echo back received data (simple echo for testing)
                if (len < TCP_BUFFER_SIZE) {
                    memcpy(tcp_send_buffer, tcp_recv_buffer, len);
                    tcp_send(socket, tcp_send_buffer, len);
                }
            }
            break;
    }
    
    return 0;  // Success
}

// Initialize TCP server
void init_tcp_server(void) {
    U8 i;
    
    printf("Initializing TCP Server on port %d...\n", TCP_SERVER_PORT);
    
    // Initialize TCP sockets
    for (i = 0; i < MAX_TCP_CLIENTS; i++) {
        tcp_server[i].LocalPort = TCP_SERVER_PORT;
        tcp_server[i].cb_func = tcp_server_callback;
        tcp_server[i].State = TCP_STATE_CLOSED;
    }
    
    // Start listening for incoming connections
    if (tcp_listen(&tcp_server[0]) == 0) {
        printf("TCP Server started successfully\n");
        tcp_server_active = 1;
    } else {
        printf("Failed to start TCP Server\n");
        tcp_server_active = 0;
    }
}

// Send meteo data to LabVIEW
void send_meteo_data_to_tcp(void) {
    if (!tcp_server_active) return;
    
    U8 socket = 0;  // Use first socket
    U16 len;
    
    // Format data for LabVIEW (simple CSV format)
    len = sprintf((char*)tcp_send_buffer, 
                  "Temperature: %.2f,Pressure: %.2f,Humidity: %.2f,WindSpeed: %.2f,WindDir: %.2f\n",
                  temperatura, davlenie, vlaga, skorost, napravlenieVetra);
    
    // Send data to connected LabVIEW client
    if (tcp_send(socket, tcp_send_buffer, len) == 0) {
        printf("Sent meteo data to LabVIEW\n");
    }
}

// Process TCP server (call this periodically)
void process_tcp_server(void) {
    if (tcp_server_active) {
        // Poll TCP sockets
        tcp_poll_sockets();
        
        // Send meteo data every time (you can add timing here)
        send_meteo_data_to_tcp();
    }
}

// Check if TCP server is active
BOOL is_tcp_server_active(void) {
    return tcp_server_active;
}