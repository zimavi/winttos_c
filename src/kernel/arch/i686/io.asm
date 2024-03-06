[bits 32]

global i686_outb
i686_outb:
    [bits 32]
    mov dx, [esp + 4]
    mov al, [esp + 8]
    out dx, al
    ret

global i686_inb
i686_inb:
    [bits 32]
    mov dx, [esp + 4]
    xor eax, eax
    in al, dx
    ret

;
; void __panic()
;
global __panic
__panic:
    cli
    hlt

;
; void __attribute__((cdecl)) i686_EnableInterrupts()
;
global i686_EnableInterrupts
i686_EnableInterrupts:
    sti
    ret

;
; void __attribute__((cdecl)) i686_DisableInterrupts()
;
global i686_DisableInterrupts:
i686_DisableInterrupts:
    cli
    ret

global crash_me
crash_me:
    mov ecx, 0xdeadbeef
    xor eax, eax
    div eax

    ret

;
; void sys_panic()
;
global sys_panic
sys_panic:
    mov eax, 0xDE
    int 0x80
    ret