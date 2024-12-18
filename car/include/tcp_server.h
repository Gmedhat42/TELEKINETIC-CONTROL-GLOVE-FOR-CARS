#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/tcp.h"

// Define the custom message handler type
typedef void (*tcp_message_handler_t)(const char *message, size_t length, struct tcp_pcb *tpcb);

// Functions
static err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static err_t tcp_server_accept(void *arg, struct tcp_pcb *newpcb, err_t err);
void tcp_server_init(tcp_message_handler_t handler);

#endif // TCP_SERVER_H
