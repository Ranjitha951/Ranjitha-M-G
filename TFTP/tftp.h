/* Common file for server & client*/

#ifndef TFTP_H
#define TFTP_H

#include <stdint.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define RED         "\033[1;3;31m"
#define GREEN       "\033[1;32m"
#define YELLOW      "\033[0;3;33m"
#define BLUE        "\033[1;3;34m"
#define MAGENTA     "\033[1;3;35m"
#define CYAN        "\033[1;3;36m"
#define RESET       "\033[0m"



#define PORT 6969
#define BUFFER_SIZE 516  // TFTP data packet size (512 bytes data + 4 bytes header)
#define TIMEOUT_SEC 5    // Timeout in seconds

// TFTP OpCodes
typedef enum {
    RRQ = 1,  // Read Request
    WRQ = 2,  // Write Request
    DATA = 3, // Data Packet
    ACK = 4,  // Acknowledgment
    ERROR = 5 // Error Packet
} tftp_opcode;

// TFTP Packet Structure
typedef struct {
    uint16_t opcode; // Operation code (RRQ/WRQ/DATA/ACK/ERROR)
    union {
        struct {
            char filename[256];
            int mode;  // Typically "octet" or "Netascii"
        } request;  // RRQ and WRQ
        struct {
            uint16_t block_number;
            char data[512];
        } data_packet; // DATA
        struct {
            uint16_t block_number;
        } ack_packet; // ACK
        struct {
            uint16_t error_code;
            char error_msg[512];
        } error_packet; // ERROR
    } body;
} tftp_packet;

void send_file(int sockfd, struct sockaddr_in client_addr, socklen_t client_len, char *filename);
void receive_file(int sockfd, struct sockaddr_in client_addr, socklen_t client_len, char *filename);


#endif // TFTP_H
