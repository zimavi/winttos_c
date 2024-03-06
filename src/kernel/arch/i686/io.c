#include "io.h"
#include <stdio.h>

#define UNUSED_PORT         0x80

void __panic();

void i686_iowait()
{
    i686_outb(UNUSED_PORT, 0);
}

void i686_panic(Registers* regs)
{
    bdg_enableOutput();

    uint32_t interrupt = regs->interrupt;

    printf("Unhandled exception %d '%s'\r\n", interrupt, g_Exceptions[interrupt]);
    printf("  eax=%x  ebx=%x  ecx=%x  edx=%x  esi=%x  edi=%x\r\n",
        regs->eax, regs->ebx, regs->ecx, regs->edx, regs->esi, regs->edi);

    printf("  esp=%x  ebp=%x  eip=%x  eflags=%x  ds=%x  cs=%x  ss=%x\r\n",
        regs->esp, regs->ebp, regs->eip, regs->eflags, regs->cs, regs->ds, regs->ss);

    printf("  interrupt=%x  errorcode=%x\r\n", regs->interrupt, regs->error);

    printf("KERNEL PANIC!\r\n");

    __panic();
}