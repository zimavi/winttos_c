#include <stdint.h>
#include "stdio.h"
#include "memory.h"
#include <hal/hal.h>
#include <arch/i686/isr.h>
#include <arch/i686/irq.h>
#include <arch/i686/io.h>
#include <arch/i686/syscalls.h>
#include <string.h>

#define __WINTT_DEBUG

void HandleSyscallInt(Registers* regs);

extern uint8_t __bss_start;
extern uint8_t __end;

void dummy_timer(Registers* regs)
{

}

void __attribute__((section(".entry"))) start(uint16_t bootDrive)
{
    memset(&__bss_start, 0, (&__end) - (&__bss_start));

#ifdef __WINTT_DEBUG

    bdg_enableOutput();

#endif

    clrscr();

    HAL_Initialize();

    printf("Hello world from kernel!!!\n");

    //i686_ISR_RegisterHandler(0x80, HandleSyscallInt);

    i686_IntSyscall_Initialize();
    i686_Sysenter_Initialize();

    i686_IRQ_RegisterHandler(0, dummy_timer);

    const char* test = "Hello from syscall!!!!!\n\0";
    sys_write(1, test, strlen(test));
    //sys_zero();
end:
    for (;;);
}

void HandleSyscallInt(Registers* regs) 
{
    printf("Unknown syscall (eax=%x)\r\n", regs->eax);
}