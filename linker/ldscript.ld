/* Linker script for RP2350 (Raspberry Pi Pico 2) with TrustZone */

MEMORY {
    FLASH_S (rx)  : ORIGIN = 0x00000000, LENGTH = 2M   /* Secure Flash */
    FLASH_NS (rx) : ORIGIN = 0x10000000, LENGTH = 2M   /* Non-Secure Flash */
    SRAM_S (rwx)  : ORIGIN = 0x20000000, LENGTH = 256K /* Secure SRAM (on-chip) */
    SRAM_NS (rwx) : ORIGIN = 0x20040000, LENGTH = 256K /* Non-Secure SRAM (on-chip) */
}

/* Entry point of the application */
ENTRY(Reset_Handler)

SECTIONS {
    /* Secure Code Section */
    .text : {
        KEEP(*(.isr_vector))     /* Interrupt Vector Table */
        *(.text*)               /* Code */
        *(.rodata*)             /* Read-only data */
    } > FLASH_S

    /* Non-Secure Code Section */
    .text_ns : {
        KEEP(*(.isr_vector_ns)) /* Non-Secure Interrupt Vector Table */
        *(.text_ns*)            /* Non-Secure Code */
        *(.rodata_ns*)          /* Non-Secure Read-only data */
    } > FLASH_NS

    /* Secure Data Section */
    _sidata = .;
    .data : {
        _sdata = .;
        *(.data*)               /* Initialized data */
        _edata = .;             /* End of Secure initialized data */
    } > SRAM_S AT > FLASH_S

    .bss : {
        _sbss = .;
        *(.bss*)                /* Zero-initialized data */
        _ebss = .;
    } > SRAM_S

    /* Non-Secure Data Section */
    .data_ns : {
        _sdata_ns = .;
        *(.data_ns*)            /* Non-Secure Initialized data */
        _edata_ns = .;          /* End of Non-Secure initialized data */
    } > SRAM_NS AT > FLASH_NS

    .bss_ns : {
        _sbss_ns = .;
        *(.bss_ns*)             /* Non-Secure Zero-initialized data */
        _ebss_ns = .;
    } > SRAM_NS

    /* Stack for Secure and Non-Secure Worlds */
    .stack (NOLOAD) : {
        _sstack = .;
        . += 0x4000;            /* Allocate 16KB for the secure stack */
        _estack = .;
    } > SRAM_S

    .stack_ns (NOLOAD) : {
        _sstack_ns = .;
        . += 0x4000;            /* Allocate 16KB for the non-secure stack */
        _estack_ns = .;
    } > SRAM_NS

    /* Define end of memory */
    _end = .;
}

