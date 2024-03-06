#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    const char* Name;
    bool (*Probe)();
    void (*Initialize)(uint8_t offsetPic1, uint8_t offsetPic2, bool autoEoi);
    void (*Disable)();
    void (*Mask)(int irq);
    void (*Unmask)(int irq);
    void (*SendEOI)(int irq);
    
} PICDriver;