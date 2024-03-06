#include <util/defs.h>
#include <stdint.h>
#include <stdio.h>
#include "isr.h"

#define STDIN_FILENO    1

// uint32_t ASMCALL Syscall_x86_Handler(Registers* regs)
// {
//     printf("It works!");
//     return 1;
// }

void __attribute__((cdecl)) Interrupt128Handler(Registers* regs);

void i686_InterruptSyscall_Initialize()
{
    i686_ISR_RegisterHandler(0x80, Interrupt128Handler);
}

void __attribute__((cdecl)) Interrupt128Handler(Registers* regs)
{
    if(regs->eax == 4)
    {
        if(regs->ebx == STDIN_FILENO)
        {
            const char* str = (const char*)regs->ecx;
            for(int i = 0; i < regs->edx; i++)
            {
                putc(*str);
                ++str;
            }
        }
    }
    else
        printf("invalid syscal %d!\r\n", regs->eax);
}