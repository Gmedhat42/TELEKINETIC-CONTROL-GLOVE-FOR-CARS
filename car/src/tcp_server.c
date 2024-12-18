#include "tcp_server.h"

// Global variable to store the custom message handler
static tcp_message_handler_t custom_handler = NULL;

// Function to handle received data
static err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
    if (p == NULL)
    {
        // Client disconnected
        tcp_close(tpcb);
        return ERR_OK;
    }

    // Call the custom handler if set
    if (custom_handler)
    {
        custom_handler((const char *)p->payload, p->len, tpcb);
    }

    // Free the received buffer
    pbuf_free(p);
    return ERR_OK;
}

// Function to handle a new connection
static err_t tcp_server_accept(void *arg, struct tcp_pcb *newpcb, err_t err)
{
    printf("Client connected\n");
    tcp_recv(newpcb, tcp_server_recv); // Set receive callback
    return ERR_OK;
}

// Initialize the TCP server with a custom message handler
void tcp_server_init(tcp_message_handler_t handler)
{
    // Store the handler for later use
    custom_handler = handler;

    struct tcp_pcb *pcb = tcp_new(); // Create a new TCP control block
    if (!pcb)
    {
        printf("Failed to create PCB\n");
        return;
    }

    // Bind to port 1234
    if (tcp_bind(pcb, IP_ADDR_ANY, 1234) != ERR_OK)
    {
        printf("Failed to bind PCB\n");
        return;
    }

    // Start listening for incoming connections
    pcb = tcp_listen(pcb);
    tcp_accept(pcb, tcp_server_accept); // Set accept callback
    printf("TCP Server listening on port 1234\n");
}
