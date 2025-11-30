cmake_minimum_required(VERSION 3.12)

include(pico-sdk/pico_sdk_init.cmake)

project(pico-kb C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

pico_sdk_init()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(FAMILY rp2040)
set(BOARD pico_sdk)

add_executable(
    kb_firmware
    src/main.c
)

target_include_directories(
    kb_firmware
    PRIVATE src
)

target_link_libraries(kb_firmware PUBLIC pico_stdlib pico_unique_id tinyusb_device tinyusb_board)


