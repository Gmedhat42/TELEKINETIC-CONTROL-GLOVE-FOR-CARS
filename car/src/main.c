#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "led.h"
#include "buzzer.h"
#include "ultrasonic.h"
#include "motor_driver.h"
#include "tcp_server.h"

// Define I2C Pins and Speed for the MPU6050
#define SDA_PIN 4
#define SCL_PIN 5
#define I2C_SPEED 100000 // 100 kHz

// Define pins for ultrasonic
#define TRIG 14
#define ECHO 15

// Define pins for LED and BUZZER
#define LED_PIN 12
#define BUZZER_PIN 13

// Define boolean for ultrasonic interrupt
bool obstacle_ahead = false;

// WiFi credentials
const char WIFI_SSID[] = "Etisalat 4G iModem-08ED";
const char WIFI_PASSWORD[] = "12903435";

void test_braking_submodule()
{
    sensor_init(TRIG, ECHO);
    LED_Init(LED_PIN);
    BUZZER_Init(BUZZER_PIN);

    float distance;

    while (1)
    {
        distance = measure_distance(TRIG, ECHO);
        printf("distance=%f \n", distance);
        if (distance < 10 && distance > 0)
        {
            LED_On(LED_PIN);
            BUZZER_On(BUZZER_PIN);
            // stop motors
            motor_control(0, 5);
        }
        else
        {
            LED_Off(LED_PIN);
            BUZZER_Off(BUZZER_PIN);
        }
        Delay(100);
    }
}

void test_motors()
{
    motor_init();

    while (1)
    {
        motor_control(255, 3);

        Delay(1000);
        motor_control(0, 5);
        Delay(250);

        motor_control(128, 4);

        Delay(1000);
        motor_control(0, 5);
        Delay(250);

        motor_control(255, 1);

        Delay(1000);
        motor_control(0, 5);
        Delay(250);

        motor_control(255, 2);

        Delay(1000);
        motor_control(0, 5);
        Delay(2000);
    }
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

// Custom handler for received messages
// Custom handler for received messages
void handle_client_message(const char *message, size_t length, struct tcp_pcb *tpcb)
{
    printf("Received: %.*s\n", (int)length, message);

    // Respond to the client
    const char *response = "Message received successfully!";
    // tcp_server_send_response(tpcb, response, strlen(response));

    // Split the message into two parts: pitch and roll
    char message_copy[100];
    strncpy(message_copy, message, sizeof(message_copy));
    message_copy[sizeof(message_copy) - 1] = '\0'; // Ensure null-termination

    float pitch, roll;
    if (sscanf(message_copy, "Pitch: %f, Roll: %f", &pitch, &roll) == 2)
    {
        printf("Parsed Pitch: %.2f, Roll: %.2f\n", pitch, roll);

        // Determine the dominant angle (favor bigger magnitude)
        float abs_pitch = fabs(pitch);
        float abs_roll = fabs(roll);

        if (abs_pitch < 10 && abs_roll < 10)
        {
            motor_control(0, 5); // Stop motors
            printf("Action: Stop\n");
        }
        else if (abs_pitch > abs_roll)
        {
            if (pitch < 0)
            {
                if (obstacle_ahead)
                {
                    motor_control(0, 5); // Stop motors
                    printf("Action: Stop\n");
                }
                else
                {
                    // Forward
                    motor_control(170, 3); // Full speed forward
                    printf("Action: Forward\n");
                }
            }
            else
            {
                // Backward
                motor_control(170, 4); // Full speed backward
                printf("Action: Backward\n");
            }
        }
        else
        {
            if (roll > 0)
            {
                // Spin Clockwise (CW)
                motor_control(170, 2); // Full speed spin CW
                printf("Action: Spin Clockwise\n");
            }
            else
            {
                // Spin Anti-clockwise (ACW)
                motor_control(170, 1); // Full speed spin ACW
                printf("Action: Spin Anti-clockwise\n");
            }
        }
    }
    else
    {
        printf("Failed to parse pitch and roll.\n");
    }
}

int start_tcp_server()
{
    // Initialize the TCP server
    tcp_server_init(handle_client_message);
}

int main()
{
    stdio_init_all();

    // Initialize the tcp connection
    init_tcp_connection();

    // Initialize the motor driver
    motor_init();

    // Initialize the auto-braking system
    sensor_init(TRIG, ECHO);
    LED_Init(LED_PIN);
    BUZZER_Init(BUZZER_PIN);

    // Test DC Motors
    // test_motors();

    // Test emergency braking
    // test_braking_submodule();

    // Test TCP Server
    start_tcp_server();

    while (1)
    {
        float distance;
        distance = measure_distance(TRIG, ECHO);
        // printf("distance=%f \n", distance);
        if (distance < 20 && distance > 0)
        {
            LED_On(LED_PIN);
            BUZZER_On(BUZZER_PIN);
            obstacle_ahead = true;
        }
        else
        {
            LED_Off(LED_PIN);
            BUZZER_Off(BUZZER_PIN);
            obstacle_ahead = false;
        }
        Delay(50);
    }

    return 0;
}
