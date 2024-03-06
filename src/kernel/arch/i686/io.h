#pragma once

#include <stdint.h>
#include "isr.h"

#define STI                         i686_EnableInterrupts();
#define CLI                         i686_DisableInterrupts();

void __attribute__((cdecl)) i686_outb(uint16_t port, uint8_t value);
uint8_t __attribute__((cdecl)) i686_inb(uint16_t port);
void __attribute__((cdecl)) i686_EnableInterrupts();
void __attribute__((cdecl)) i686_DisableInterrupts();

void i686_iowait();
void i686_panic(Registers* regs);