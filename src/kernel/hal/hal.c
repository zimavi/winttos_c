#include "hal.h"
#include <arch/i686/gdt.h>
#include <arch/i686/idt.h>
#include <arch/i686/isr.h>
#include <arch/i686/irq.h>
#include <arch/i686/timer.h>
#include <arch/i686/keyboard.h>

void HAL_Initialize()
{
    i686_GDT_Initialize();
    i686_IDT_Initialize();
    i686_ISR_Initialize();
    i686_IRQ_Initialize();
    //i686_PIT_Initialize();

    //
    // FIXME:
    // - Wrong keyboard mapping
    //i686_Keyboard_Initialize();
}