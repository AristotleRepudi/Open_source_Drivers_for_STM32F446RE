#include<stdint.h>

extern uint32_t _estack;
extern uint32_t _stext;
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

void Reset_Handler(void);
int main();

void NMI_Handler() __attribute__((weak,alias("Default_Handler")));
void HardFault_Handler() __attribute__((weak,alias("Default_Handler")));

void Default_Handler(){
    while(1);
}

uint32_t vector_table[] __attribute__((section(".isr_vector_tbl")))={
    (uint32_t)&_estack,
    (uint32_t)&Reset_Handler,
    (uint32_t)&NMI_Handler,
    (uint32_t)&HardFault_Handler
};

void Reset_Handler()
{
    uint32_t *psrc = &_etext;
    uint32_t *pdst = &_sdata;

    while(pdst < &_edata)
    {
        *pdst++ = *psrc++;
    }

    pdst = &_sbss;

    while(pdst < &_ebss)
    {
        *pdst++ = 0;
    }

    main();

    while(1);
}
