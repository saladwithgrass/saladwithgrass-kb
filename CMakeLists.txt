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
    ${PROJECT_NAME}
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_sources(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/keyboard_config.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/usb_descriptors.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/pin_polling.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/keymap.c
)

target_link_libraries(
    ${PROJECT_NAME} PUBLIC 
    pico_stdlib pico_unique_id tinyusb_device tinyusb_board 
)


