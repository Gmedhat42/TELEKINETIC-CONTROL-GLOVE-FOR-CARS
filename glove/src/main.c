#include <stdio.h>
#include "pico/stdlib.h"
#include "mpu6050.h"
#include "tcp_client.h"

// Define I2C Pins and Speed for the MPU6050
#define SDA_PIN 4
#define SCL_PIN 5
#define I2C_SPEED 100000 // 100 kHz

// WiFi credentials
const char WIFI_SSID[] = "Etisalat 4G iModem-08ED";
const char WIFI_PASSWORD[] = "12903435";

char *mpu6050_get()
{
    // Initialize the MPU6050 in main

    int16_t acceleration[3];
    float pitch, roll;

    // Read accelerometer data and calculate pitch/roll
    mpu6050_read_acceleration(acceleration);
    calculate_pitch_roll(acceleration, &pitch, &roll);

    // return pitch and roll
    char *result = (char *)malloc(50);
    sprintf(result, "Pitch: %f, Roll: %f", pitch, roll);
    return result;
}

int init_tcp_connection()
{
    printf("Starting TCP \n");

    if (cyw43_arch_init())
    {
        printf("WiFi init failed\n");
        return -1;
    }

    cyw43_arch_enable_sta_mode();

    printf("Connecting to WiFi...\n");
    if (cyw43_arch_wifi_connect_blocking(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK) != 0)
    {
        printf("WiFi connection failed\n");
        return -1;
    }
    printf("Connected to WiFi\n");
}

int tcp_client_send(char *message)
{
    // Initialize the TCP client with the message
    tcp_client_init(message);
}

int main()
{
    stdio_init_all();

    // Initialize the MPU6050
    mpu6050_init(SDA_PIN, SCL_PIN, I2C_SPEED);

    // Initialize the tcp connection
    init_tcp_connection();

    // Test TCP Client
    while (1)
    {
        char *message = mpu6050_get();
        tcp_client_send(message);
        free(message);
        sleep_ms(100);
    }

    return 0;
}
