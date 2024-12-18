#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

// Server address and port to connect to
#define SERVER_IP "192.168.0.190" // Replace with the server's IP address
#define SERVER_PORT 1234

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/tcp.h"

static err_t tcp_client_connected(void *arg, struct tcp_pcb *tpcb, err_t err);
void tcp_client_init(const char *message);

#endif // TCP_CLIENT_H
