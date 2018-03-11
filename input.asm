global _get_key

section .text
_get_key:
    mov ah, 0x00
    int 0x16
    shr ax, 8
    ret
