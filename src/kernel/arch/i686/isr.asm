[bits 32]

extern i686_ISR_Handler

%macro ISR_NOERRORCODE 1
global i686_ISR%1
i686_ISR%1:
    push 0              ; dummy error code
    push %1             ; push interrupt number
    jmp isr_common

%endmacro

%macro ISR_ERRORCODE 1
global i686_ISR%1
i686_ISR%1:
                        ; error code is pushed by CPU
    push %1             ; push interrupt number
    jmp isr_common

%endmacro

%include "arch/i686/isrs_gen.inc"
isr_common:
    pusha

    xor eax, eax
    mov ax, ds
    push eax

    mov ax, 0x10        ; use kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    push esp            ; pass pointer to stack to C, so we can access all pushed info
    call i686_ISR_Handler
    add esp, 4

    pop eax             ; restore old segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    popa                ; pop everything else
    add esp, 8          ; remove interrupt number + error code
    iret                ; return from interrupt