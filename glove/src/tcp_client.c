#include "tcp_client.h"

// LWIP TCP connection callback function
static err_t tcp_client_connected(void *arg, struct tcp_pcb *tpcb, err_t err)
{
    if (err != ERR_OK)
    {
        printf("Connection failed: %d\n", err);
        return err;
    }

    printf("Connected to the server\n");

    // Send the message passed via `arg`
    const char *message = (const char *)arg;
    tcp_write(tpcb, message, strlen(message), TCP_WRITE_FLAG_COPY);

    // Optionally, close the connection after sending
    tcp_close(tpcb);
    printf("Sent message: %s\n", message);
    printf("Connection closed\n");

    return ERR_OK;
}

// Initialize the TCP client
void tcp_client_init(const char *message)
{
    struct tcp_pcb *pcb = tcp_new(); // Create a new TCP control block
    if (!pcb)
    {
        printf("Failed to create PCB\n");
        return;
    }

    // Convert server IP to LWIP format
    ip4_addr_t server_ip;
    if (!ip4addr_aton(SERVER_IP, &server_ip))
    {
        printf("Invalid server IP address\n");
        return;
    }

    // Connect to the server and pass the message as the argument
    err_t err = tcp_connect(pcb, &server_ip, SERVER_PORT, tcp_client_connected);
    if (err != ERR_OK)
    {
        printf("Failed to connect to the server: %d\n", err);
        tcp_close(pcb);
    }
    else
    {
        printf("Connecting to server %s:%d...\n", SERVER_IP, SERVER_PORT);
        tcp_arg(pcb, (void *)message); // Set the message as the argument
    }
}
