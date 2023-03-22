cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico_pio C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init() 

add_executable(hello_pio)


target_sources(hello_pio PRIVATE hello.c)

target_link_libraries(hello_pio PRIVATE
        pico_stdlib
        hardware_pio
        hardware_dma
        hardware_i2c
        )

pico_enable_stdio_usb(hello_pio 1)
#pico_enable_stdio_uart(hello_pio 0)
pico_add_extra_outputs(hello_pio)

# add url via pico_set_program_url
