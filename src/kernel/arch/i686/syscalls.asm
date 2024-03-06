section .text
;
; void ASMCALL i686_Sysenter_Initialize();
;
global i686_Sysenter_Initialize
i686_Sysenter_Initialize:
    mov eax, 0x174  ; SYSENTER_CS_MSR
    mov edx, cs     ; Kernel's code segment
    xor ecx, ecx
    wrmsr

    mov eax, 0x175  ; SYS_ENTER_ESP_MSR
    mov edx, esp    ; Kernel's stack pointer
    xor ecx, ecx
    wrmsr

    mov eax, 0x176  ; SYSENTER_EIP_MSR, AKA: Syscall handler entry
    mov edx, sysenter_handler
    xor ecx, ecx
    wrmsr

    ret


extern Syscall_x86_Handler
sysenter_handler:
    pusha                       ; save all registers

    ; Setup registers
    push edi
    push esi
    push edx
    push ecx
    push ebx
    push eax

    call sysenter_handler
    
    add esp, 24                 ; poping all variables (cdecl cleaning up)

    mov [ret_val], eax          ; save return value

    popa                        ; restore registers

    mov eax, [ret_val]

    sysexit

;
; uint32_t __attribute__((cdecl)) sys_zero()
;
global sys_zero         ; testing
sys_zero:
    push eax
    xor eax, eax

    int 0x80
    ;sysenter            ; DOESNT WORK!

    pop eax
    ret


;
; uint32_t __attribute__((cdecl)) sys_write(uint32_t fd, char* buf, uint8_t count)
;
global sys_write
sys_write:
    ; make new call frame
    push ebp            ; save old call frame
    mov ebp, esp        ; initialize new call frame

    push ebx

    ; setup params
    mov eax, 4          ; syscall number
    mov ebx, [ebp + 8]  ; fd
    mov ecx, [ebp + 12] ; buf
    mov edx, [ebp + 16] ; count

    int 0x80            ; make syscall

    pop ebx

    ; restore old call frame
    mov esp, ebp
    pop ebp
    ret


section .data
ret_val: dd 0