/* Startup file for Cortex-M33 with TrustZone (RP2350) */

.extern main
.extern main_ns

    /* Secure Reset Handler */
    void
    Reset_Handler(void);

/* Default IRQ Handlers */
void Default_Handler(void);

/* Exception and Interrupt Vector Table (Secure) */
__attribute__((section(".isr_vector"))) void (*const SecureVectors[])(void) = {
    (void (*)(void))((unsigned long)&_estack), /* Initial Stack Pointer */
    Reset_Handler,                             /* Reset Handler */
    Default_Handler,                           /* NMI Handler */
    Default_Handler,                           /* HardFault Handler */
    Default_Handler,                           /* Reserved */
    Default_Handler,                           /* Reserved */
    Default_Handler,                           /* Reserved */
    Default_Handler,                           /* SecureFault Handler */
    Default_Handler,                           /* Reserved */
    Default_Handler,                           /* Reserved */
    Default_Handler,                           /* Reserved */
    Default_Handler,                           /* SVCall Handler */
    Default_Handler,                           /* Reserved */
    Default_Handler,                           /* Reserved */
    Default_Handler,                           /* PendSV Handler */
    Default_Handler,                           /* SysTick Handler */
    /* Add peripheral interrupts here */
};

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

  /* Jump to Non-Secure main */
  extern void NSC_Init(void);
  NSC_Init(); // Initialize Secure Gateway calls if necessary

  /* Start Non-Secure main */
  void (*non_secure_main)(void) = (void (*)(void))main_ns;
  non_secure_main();

  /* Should never return */
  while (1)
    ;
}

/* Default Handler for unused interrupts */
void Default_Handler(void) {
  while (1)
    ;
}
