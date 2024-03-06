#pragma once

#include <arch/i686/io.h>
#include <stdio.h>

// +=+=+=+=+=+=+=+=+=+=+
// |       DEBUG       |
// +=+=+=+=+=+=+=+=+=+=+
#define prt_error(msg, ...)     printf("[!]" msg, __VA_ARGS__)
#define prt_info(msg, ...)      printf("[*]" msg, __VA_ARGS__)
#define prt_ok(msg, ...)        printf("[+]" msg, __VA_ARGS__)

#define dbg_out(msg)            i686_outb(0xE9, msg);
