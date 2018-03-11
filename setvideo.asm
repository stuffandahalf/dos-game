global _set_video_mode

section .text
_set_video_mode:
    push ebp
    mov ebp, esp
    mov ah, 0x00
    mov al, [ebp+8]
    int 0x10
    leave
    ret
