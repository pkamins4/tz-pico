#include <stdint.h>

/* External declarations */
extern void Reset_Handler(void);           /* Reset Handler */
extern void Default_Handler(void);         /* Default IRQ Handlers */
extern void __TZ_set_MSP_NS(uint32_t);    /* Function to set Non-Secure MSP */

/* Function declarations */
void NSC_Init(void);                      /* Initialize Non-Secure World */
void main_ns(void);                       /* Non-Secure main entry point */
int main(void);                           /* Secure main entry point */


void __TZ_set_MSP_NS(uint32_t stack_pointer){
__asm volatile ( 
    "MSR MSP_NS, %0" : : "r" (stack_pointer) 
);
}
/* Secure Reset Handler */
void Reset_Handler(void) {
    /* Copy initialized data from Flash to SRAM */
    extern unsigned long _sdata, _edata, _sidata;
    unsigned long *src = &_sidata;
    unsigned long *dst = &_sdata;

    while (dst < &_edata) {
        *dst++ = *src++;
    }

    /* Zero-initialize the .bss section */
    extern unsigned long _sbss, _ebss;
    dst = &_sbss;

    while (dst < &_ebss) {
        *dst++ = 0;
    }

    /* Set Non-Secure MSP */
    extern unsigned long _sstack_ns;
    __TZ_set_MSP_NS((uint32_t)&_sstack_ns);

    /* Initialize Secure Gateway Calls if necessary */
    NSC_Init();

    /* Jump to Non-Secure world */
    main_ns();  /* This will never return */
}

/* Default Handler for unused interrupts */
void Default_Handler(void) {
    while (1);  /* Hang in an infinite loop if an interrupt occurs */
}

/* Non-Secure Initialization Function */
void NSC_Init(void) {
    /* Set up secure gateway calls, if needed for communication between Secure and Non-Secure worlds */
    /* This might involve configuring certain peripherals or memory-mapped registers */
    /* For simplicity, this is just a placeholder function */
}

/* Non-Secure Main Entry Point */
void main_ns(void) {
    /* Non-Secure world application code starts here */

    /* Initialize system for the Non-Secure world */
    // Example: Initialize peripherals, memory, etc.

    /* Call the Non-Secure main application function */
    main();  /* Start secure world application code */
}

/* Secure World Main Entry Point */
int main(void) {
    /* Secure world application code */
    // Example: Secure operations like setting up secure peripherals or handling security features

    while (1) {
        /* Secure world main loop */
    }
}
extern unsigned long _estack;
/* Interrupt Vector Table (Secure) */
__attribute__((section(".isr_vector")))
void (* const SecureVectors[])(void) = {
    (void (*)(void))((unsigned long)&_estack),   /* Initial Stack Pointer */
    Reset_Handler,                               /* Reset Handler */
    Default_Handler,                             /* NMI Handler */
    Default_Handler,                             /* HardFault Handler */
    Default_Handler,                             /* Reserved */
    Default_Handler,                             /* Reserved */
    Default_Handler,                             /* Reserved */
    Default_Handler,                             /* SecureFault Handler */
    Default_Handler,                             /* Reserved */
    Default_Handler,                             /* Reserved */
    Default_Handler,                             /* Reserved */
    Default_Handler,                             /* SVCall Handler */
    Default_Handler,                             /* Reserved */
    Default_Handler,                             /* Reserved */
    Default_Handler,                             /* PendSV Handler */
    Default_Handler,                             /* SysTick Handler */
    /* Add peripheral interrupts here */
};

/* End of main.c */

