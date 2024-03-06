#include <util/defs.h>
#include <stdint.h>
#include <stdio.h>
#include "isr.h"

#define STDIN_FILENO    1

typedef struct {
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
} __attribute__((packed)) SyscallParams;

uint32_t __attribute__((cdecl)) Syscall_x86_Handler(SyscallParams params)
{
    printf("sysenter works!");
    return 0;
}

void __attribute__((cdecl)) Interrupt128Handler(Registers* regs);

void i686_IntSyscall_Initialize()
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
        printf("invalid syscall %d!\r\n", regs->eax);
}