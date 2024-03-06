#include "irq.h"
#include "pic.h"
#include "i8259.h"
#include "io.h"
#include <stddef.h>
#include <stdio.h>
#include <util/arrays.h>

#define PIC_REMAP_OFFSET            0x20

void sys_panic();

IRQHandler g_IRQHandlers[16];
static const PICDriver* g_Driver = NULL;

void i686_IRQ_Handler(Registers* regs)
{
    int irq = regs->interrupt - PIC_REMAP_OFFSET;

    if(g_IRQHandlers[irq] != NULL)
    {
        g_IRQHandlers[irq](regs);
    }
    else
    {
        printf("Unhandled IRQ %d\r\n", irq);
    }

    // send EOI to both PIC
    g_Driver->SendEOI(irq);
}

void i686_IRQ_Initialize()
{
    const PICDriver* drivers[] = {
        i8259_GetDriver(),
    };

    for(int i = 0; i < SIZE(drivers); i++)
    {
        if(drivers[i]->Probe())
        {
            g_Driver = drivers[i];
        }
    }

    if(g_Driver == NULL)
    {
        printf("Warning: No PIC found!");
        sys_panic();
        return;
    }

    printf("Found %s PIC.\r\n", g_Driver->Name);
    g_Driver->Initialize(PIC_REMAP_OFFSET, PIC_REMAP_OFFSET + 8, false);
    
    // register ISR handlers for each of the 16 irq lines
    for(int i = 0; i < 16; i++)
        i686_ISR_RegisterHandler(PIC_REMAP_OFFSET + i, i686_IRQ_Handler);
    

    // enable interrupts
    STI

}

void i686_IRQ_RegisterHandler(int irq, IRQHandler handler)
{
    g_IRQHandlers[irq] = handler;
    g_Driver->Unmask(irq);
}