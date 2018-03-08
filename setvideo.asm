global _setVideoMode

section .text
_setVideoMode:
    push ebp
    mov ebp, esp
    mov ah, 0x00
    mov al, [ebp+8]
    int 0x10
    leave
    ret
