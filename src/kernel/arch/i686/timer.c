#include "timer.h"
#include "idt.h"
#include "io.h"
#include <stdint.h>
#include <stdio.h>

#define PIT_DATA_PORT0          0x40
#define PIT_DATA_PORT1          0x41
#define PIT_DATA_PORT2          0x42
#define PIT_COMMAND_PORT        0x43

enum {
    PIT_FLAGS_CHANNEL0          = 0x00,
    PIT_FLAGS_CHANNEL1          = 0x40,
    PIT_FLAGS_CHANNEL2          = 0x80,

    PIT_FLAGS_ACCES_LO          = 0x10, // AKA: Access lobyte only
    PIT_FLAGS_ACCES_HI          = 0x20, // AKA: Access hibyte only
    PIT_FLAGS_ACCES_HILO        = 0x30, // AKA: Access hibyte and lobyte

    PIT_FLAGS_OPERATION_MODE0   = 0x00, // AKA: interrupt on terminal count
    PIT_FLAGS_OPERATION_MODE1   = 0x02, // AKA: hardware re-triggerable one-shot
    PIT_FLAGS_OPERATION_MODE2   = 0x04, // AKA: rate generator
    PIT_FLAGS_OPERATION_MODE3   = 0x06, // AKA: square wave generator
    PIT_FLAGS_OPERATION_MODE4   = 0x08, // AKA: software triggered strobe
    PIT_FLAGS_OPERATION_MODE5   = 0x0A, // AKA: hardware triggered strobe
    PIT_FLAGS_OPERATION_MODE6   = 0x0C, // AKA: rate generator, same as 010b
    PIT_FLAGS_OPERATION_MODE7   = 0x0E, // AKA: square wave generator, same as 011b

    PIT_FLAGS_BINARY_MODE       = 0x00,
    PIT_FLAGS_BCD_MODE          = 0x01,
    
} PIT_FLAGS;

uint64_t g_Ticks;
const uint32_t g_Freq = 1;

void i686_PIT_HandleIRQ0(Registers* regs);

void i686_PIT_Initialize()
{
    g_Ticks = 0;
    i686_IRQ_RegisterHandler(0, i686_PIT_HandleIRQ0);

    CLI;

    // 1.1931816666 Mz
    uint32_t divisor = 1193180 / g_Freq;

    i686_outb(PIT_COMMAND_PORT, PIT_FLAGS_BINARY_MODE | PIT_FLAGS_OPERATION_MODE3 | PIT_FLAGS_ACCES_HILO | PIT_FLAGS_CHANNEL0);
    i686_iowait();
    i686_outb(PIT_DATA_PORT0, divisor & 0xFF);
    i686_iowait();
    i686_outb(PIT_DATA_PORT0, (divisor >> 8) & 0xFF);
    i686_iowait();

    STI;
}

void i686_PIT_HandleIRQ0(Registers* regs)
{
    g_Ticks++;
    putc('.');
}