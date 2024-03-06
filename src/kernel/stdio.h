#pragma once
#include <stdint.h>

void clrscr();
void putc(char c);
void puts(const char* str);
void printf(const char* fmt, ...);
void print_buffer(const char* msg, const void* buffer, uint32_t count);

// DEBUGGING

void dbg_putchr(char chr);
void dbg_putstr(const char* str);
void bdg_enableOutput();
void bdg_disableOutput();