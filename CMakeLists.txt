cmake_minimum_required(VERSION 3.10)

# Define project name and version
project(RP2350_TrustZone_Project VERSION 1.0)

# Set the toolchain (e.g., for ARM Cortex-M33)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Set the path to the ARM GCC toolchain
set(TOOLCHAIN_PREFIX arm-none-eabi-)

# Set the target architecture and options
set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}as)
set(CMAKE_LINKER ${TOOLCHAIN_PREFIX}ld)
set(CMAKE_OBJCOPY ${TOOLCHAIN_PREFIX}objcopy)

# Define the flags to be used for the ARM toolchain
set(CMAKE_C_FLAGS "-mcpu=cortex-m33 -mthumb -ffunction-sections -fdata-sections -O2 -g -nostartfiles -ffreestanding")
set(CMAKE_ASM_FLAGS "-mcpu=cortex-m33 -mthumb")
set(CMAKE_EXE_LINKER_FLAGS "-T /home/piotr-kaminski/dev/git/rpi2350/ld-test/linker/ldscript.ld")

# Set the source and include directories
include_directories(src)

# Define the source files for the project
set(SOURCES
    src/main.c
)

# Create the executable
add_executable(firmware.elf ${SOURCES})
