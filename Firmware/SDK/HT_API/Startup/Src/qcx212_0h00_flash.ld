
/* Entry Point */
ENTRY(Reset_Handler)

/* Specify the memory areas */
MEMORY
{
  /* 16K retention SRAM start */
  LOAD_IRAM_MCUVECTOR(rwx)         : ORIGIN = 0x00000000, LENGTH = 100
  LOAD_IRAM_MCU(rwx)               : ORIGIN = 0x00000064, LENGTH = 5K-100
  UNLOAD_DRAM_USRNV(rwx)           : ORIGIN = 0x00001400, LENGTH = 1K
  LOAD_DRAM_MCU(rwx)               : ORIGIN = 0x00001800, LENGTH = 4K
  UNLOAD_DRAM_PSPHYRET(rwx)        : ORIGIN = 0x00002800, LENGTH = 6K
  /* 16K retention SRAM end */

  LOAD_IRAM(rwx)                   : ORIGIN = 0x00004000, LENGTH = 36K
  LOAD_DRAM_SHARED(rwx)            : ORIGIN = 0x0000D000, LENGTH = 152K

  /* low power related memory start */
  LOAD_DRAM_BSP(rwx)               : ORIGIN = 0x00041000, LENGTH = 8K
  UNLOAD_DRAM_FLASHMEM(rwx)        : ORIGIN = 0x00042000, LENGTH = 7K
  UNLOAD_DRAM_SLPMEM(rwx)          : ORIGIN = 0x00043C00, LENGTH = 1K-32
  /* low power related memory end */

  FLASH_APP (rx)                   : ORIGIN = 0x00820000, LENGTH = 2560K        /* Use only the first bank */
}

/* Define output sections */
SECTIONS
{
  . = ORIGIN(FLASH_APP);
  Image$$UNLOAD_IROM$$Base = .;
  .isr_vector :
  {
    . = ALIGN(8);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(8);
  } >FLASH_APP AT>FLASH_APP

  /* The program code and other data goes into FLASH */
  .text :
  {
    . = ALIGN(8);
    *(EXCLUDE_FILE(*flash_qcx212.o *qspi_qcx212.o *cache_qcx212.o) .text*)
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))
   *(.phyCodeFlash_COMN)
   *(.phyCodeFlash_ICS)
   *(.phyCodeFlash_UL)
   *(.phyCodeFlash_RXDFE)
   *(.phyCodeFlash_CE)
   *(.phyCodeFlash_DE)
   *(.phyCodeFlash_AXC)
   *(.phyCodeFlash_RF)
   *(.phyCodeFlash_SCHD)
   *(.phyCodeFlash_MACSF)
   *(.phyCodeFlash_MEAS)
   *(.phyCodeFlash_PMU)
   *(.phyCodeFlash_OTDOA)
   *(.phyCodeFlash_SQ)
   *(.phyDataFlash)

    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
  } >FLASH_APP AT>FLASH_APP

  .unload_nocache :
  {
   . = ALIGN(128);
   Image$$UNLOAD_NOCACHE$$Base = .;

   *cache_qcx212.o (.text*)

    . = ALIGN(8);

    _etext = .;        /* define a global symbols at end of code */

  }>FLASH_APP AT>FLASH_APP

  /* used by the startup to initialize data */

  Load$$LOAD_IRAM1$$Base = LOADADDR(.ramcode1);
  .ramcode1 ORIGIN(LOAD_IRAM):
  {
    . = ALIGN(4);
    Image$$LOAD_IRAM1$$Base = .;
    *(.phyCodeSram)
    *(.ramCode)
    . = ALIGN(4);
    Image$$LOAD_IRAM1$$Limit = .;
  } >LOAD_IRAM AT>FLASH_APP

  Load$$LOAD_IRAM2$$Base = LOADADDR(.ramcode2);
  .ramcode2 : ALIGN(4)
  {
    . = ALIGN(4);
    Image$$LOAD_IRAM2$$Base = .;
    *(.phyCodeSram2)
    *(.ramCode2)
    . = ALIGN(4);
    Image$$LOAD_IRAM2$$Limit = .;
  } >LOAD_IRAM AT>FLASH_APP

  Load$$LOAD_DRAM_BSP$$Base = LOADADDR(.load_dram_bsp);
  .load_dram_bsp ORIGIN(LOAD_DRAM_BSP) :
  {
    . = ALIGN(4);
    Image$$LOAD_DRAM_BSP$$Base = .;
    *htnb32lxxx_hal_spi.o(.data*)
/*  cache_qcx212.o(.data*) */
    *flash_qcx212.o(.data*)
    *flash_qcx212_rt.o(.data*)
/*  *qspi_qcx212.o(.data*) */
/*  *gpio_qcx212.o(.data*) */
    *gpr_qcx212.o(.data*)
    *ecpm_qcx212.o(.data*)
    *bsp.o(.data*)
    *plat_config.o(.data*)
    *system_qcx212.o(.data*)
    *unilog_qcx212.o(.data*)
    *pad_qcx212.o(.data*)
    *ic_qcx212.o(.data*)
    *ec_main.o(.data*)
    *hibtimer_qcx212.o(.data*)
    *slpman_qcx212.o(.data*)
    *htnb32lxxx_hal_uart.o(.data*)
    *pmu_qcx212.o(.data*)
    *timer_qcx212.o(.data*)
    *dma_qcx212.o(.data*)
    *adc_qcx212.o(.data*)
    *wdt_qcx212.o(.data*)
    *os_exception.o(.data*)
    *uart_qcx212.o(.data*)
    *batmonraw_qcx212.o(.data*)
    *batmonraw_qcx212.o(.data*)
    . = ALIGN(4);
    Image$$LOAD_DRAM_BSP$$Limit = .;
    . = ALIGN(4);
    Image$$LOAD_DRAM_BSP$$ZI$$Base = .;
    *htnb32lxxx_hal_spi.o(.bss*)
/*  cache_qcx212.o(.bss*) */
    *flash_qcx212.o(.bss*)
    *flash_qcx212_rt.o(.bss*)
/*  *qspi_qcx212.o(.bss*) */
/*  *gpio_qcx212.o(.bss*) */
    *gpr_qcx212.o(.bss*)
    *ecpm_qcx212.o(.bss*)
    *bsp.o(.bss*)
    *plat_config.o(.bss*)
    *system_qcx212.o(.bss*)
    *unilog_qcx212.o(.bss*)
    *pad_qcx212.o(.bss*)
    *ic_qcx212.o(.bss*)
    *ec_main.o(.bss*)
    *hibtimer_qcx212.o(.bss*)
    *slpman_qcx212.o(.bss*)
    *htnb32lxxx_hal_uart.o(.bss*)
    *pmu_qcx212.o(.bss*)
    *timer_qcx212.o(.bss*)
    *dma_qcx212.o(.bss*)
    *adc_qcx212.o(.bss*)
    *wdt_qcx212.o(.bss*)
    *os_exception.o(.bss*)
    *uart_qcx212.o(.bss*)
    *batmonraw_qcx212.o(.bss*)
    *batmonraw_qcx212.o(.bss*)
    . = ALIGN(4);
    Image$$LOAD_DRAM_BSP$$ZI$$Limit = .;
  } >LOAD_DRAM_BSP AT>FLASH_APP

  Load$$LOAD_DRAM_SHARED$$Base = LOADADDR(.load_dram_shared);
  .load_dram_shared ORIGIN(LOAD_DRAM_SHARED):
  {
    . = ALIGN(4);
    Image$$LOAD_DRAM_SHARED$$Base = .;
    *(.data*)
    . = ALIGN(4);
    Image$$LOAD_DRAM_SHARED$$Limit = .;

  } >LOAD_DRAM_SHARED AT>FLASH_APP

  Load$$LOAD_DRAM_SHARED2$$Base = LOADADDR(.bss_data);
  .bss_data (NOLOAD):
  {
    . = ALIGN(4);
    Image$$LOAD_DRAM_SHARED$$ZI$$Base = .;
    *(.phyDataZI)
    *(.bss*)
    . = ALIGN(4); /* stack should be 4 byte align */
    __stack_start = .;
    *(.stack)
    __stack_end = .;
    Image$$LOAD_DRAM_SHARED$$ZI$$Limit = .;
  }>LOAD_DRAM_SHARED AT>FLASH_APP

  .unload_dram_usrnv ORIGIN(UNLOAD_DRAM_USRNV)  (NOLOAD):
  {
    *(.usrNvMem)                                    /* bss */
    Image$$UNLOAD_DRAM_USRNV$$Limit = .;
  } >UNLOAD_DRAM_USRNV

  .unload_dram_flashmem ORIGIN(UNLOAD_DRAM_FLASHMEM)  (NOLOAD):
  {
    *(.flashbackupdata)
  } >UNLOAD_DRAM_FLASHMEM

  .unload_dram_slpmem ORIGIN(UNLOAD_DRAM_SLPMEM)  (NOLOAD):
  {
    *(.sleepmem)                /* bss */
    *(.ctTimermem)          /* bss */
    *(.swcnt)                       /* bss */
  } >UNLOAD_DRAM_SLPMEM

  Load$$LOAD_IRAM_MCUVECTOR$$Base = LOADADDR(.load_iram_mcuvector);
  .load_iram_mcuvector ORIGIN(LOAD_IRAM_MCUVECTOR):
  {
    Image$$LOAD_IRAM_MCUVECTOR$$Base = .;
    KEEP(*(.mcuVector))
    Image$$LOAD_IRAM_MCUVECTOR$$Limit = .;
  } >LOAD_IRAM_MCUVECTOR AT>FLASH_APP

  Load$$LOAD_IRAM_MCU$$Base = LOADADDR(.load_iram_mcu);
  .load_iram_mcu ORIGIN(LOAD_IRAM_MCU):
  {
    Image$$LOAD_IRAM_MCU$$Base = .;
    KEEP(*(.ramBootCode))
    *(.mcuCode)
    *flash_qcx212.o(.text* .pre2RamCode)
    *qspi_qcx212.o(.text* .pre1RamCode)
    . = ALIGN(4);
    Image$$LOAD_IRAM_MCU$$Limit = .;
  } >LOAD_IRAM_MCU AT>FLASH_APP

  Load$$LOAD_DRAM_MCU$$Base = LOADADDR(.load_dram_mcu);
  .load_dram_mcu ORIGIN(LOAD_DRAM_MCU):
  {
    . = ALIGN(4);
    Image$$LOAD_DRAM_MCU$$Base = .;
    *(.ramBootRWData)
    . = ALIGN(4);
    Image$$LOAD_DRAM_MCU$$Limit = .;
    . = ALIGN(4);
    Image$$LOAD_DRAM_MCU$$ZI$$Base = .;
    *(.ramBootZIData)
    . = ALIGN(4);
    Image$$LOAD_DRAM_MCU$$ZI$$Limit = .;

  } >LOAD_DRAM_MCU AT>FLASH_APP

  Load$$UNLOAD_DRAM_PSPHYRET$$Base = LOADADDR(.unload_dram_psphyret);
  .unload_dram_psphyret ORIGIN(UNLOAD_DRAM_PSPHYRET)  (NOLOAD):
  {
    Image$$UNLOAD_DRAM_PSPHYRET$$ZI$$Base = .;
    *(.psphyret_6k)             /* bss */
    Image$$UNLOAD_DRAM_PSPHYRET$$ZI$$Limit = .;
  } >UNLOAD_DRAM_PSPHYRET AT>FLASH_APP

}

GROUP(
    libgcc.a
    libc.a
    libm.a
 )
