#pragma once

#include <stdint.h>

//
// FIXME:
// - GPF after setting up data
void __attribute__((cdecl)) i686_Sysenter_Initialize();

void i686_IntSyscall_Initialize();

// 
// SYSCALLS
// 
uint32_t __attribute__((cdecl)) sys_zero();
uint32_t __attribute__((cdecl)) sys_write(uint32_t fd, char* buf, uint8_t count);