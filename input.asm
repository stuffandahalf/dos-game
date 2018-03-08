global _getKey

section .text
_getKey:
    mov ah, 0x00
    int 0x16
    ret
