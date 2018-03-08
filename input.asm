;bits 32
global _getScancode

section .text
_getScancode:
    mov ah, 0x00
    int 0x16
    ret
