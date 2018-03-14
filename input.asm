%include "lib/c32.mac"

bits 32

;cglobal get_key_bios
;cglobal get_key_dos
;cglobal mouse_init

section .text

proc get_key_bios
    mov ah, 0x00
    int 0x16
endproc

proc get_key_dos
    mov ah, 0x06
    mov dl, 255
    int 0x21
endproc

; mouse struct macros
%define AVAILABLE 0
%define NUM_BUTTONS 2
%define X 4
%define Y 6
%define ACTIVE 8

%macro mouse_assign 2
    mov [esi+%1], %2
%endmacro 

proc mouse_init
%$m arg
    mov esi, [ebp + %$m]

    mov ax, 0x00
    int 0x33
    jz end
    
    push ax
    push bx
    
    ; init horizontal res
    mov ax, 0x07
    mov cx, 0x00
    mov dx, 320
    int 0x33
    
    ; init vertical res
    mov ax, 0x08
    mov cx, 0x00
    mov dx, 200
    int 0x33
    
    pop bx
    pop ax
    
end:
    mouse_assign AVAILABLE, ax
    mouse_assign NUM_BUTTONS, bx
    mouse_assign X, word 0x0
    mouse_assign Y, word 0x0
    mouse_assign ACTIVE, byte 0x0
endproc

proc mouse_update
%$m arg
    mov esi, [ebp + %$m]
    mov ax, 0x3
    int 0x33
    
    mouse_assign ACTIVE, bx
    mouse_assign X, cx
    mouse_assign Y, dx
endproc
