mov ax, 3
int 0x10

mov ax, 0xb800
mov ds, ax

mov byte [0], 'H'
mov byte [2], 'E'
mov byte [4], 'L'
mov byte [6], 'L'
mov byte [8], 'O'

halt:
    jmp halt

times 510 - ($ - $$) db 0x00

db 0x55, 0xaa
