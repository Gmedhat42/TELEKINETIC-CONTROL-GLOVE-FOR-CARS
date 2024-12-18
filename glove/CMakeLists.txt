cmake_minimum_required(VERSION 3.28)
include(pico_sdk_import.cmake)

set(projname "main")
set(PICO_BOARD pico_w)

project(pico_examples C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Define the target executable and link source files
add_executable(${projname}
    src/main.c
    src/MPU6050.c
    src/tcp_client.c
)

target_link_libraries(${projname}
    pico_stdlib
    hardware_spi
    hardware_i2c
    pico_binary_info
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_http
   
)

#Enable the USB Virtual COM Port
pico_enable_stdio_usb(${projname} 1)
pico_enable_stdio_uart(${projname} 0)

# Create map/bin/hex file etc.
pico_add_extra_outputs(${projname})

