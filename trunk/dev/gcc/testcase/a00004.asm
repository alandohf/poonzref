assume cs:abc
abc segment
startp:
mov ax,2000h
mov ds,ax
mov bx,0
mov al,[bx]
mov bx,1
mov bl,[bx]
mov bx,2
mov cl,[bx]
mov bx,3
mov dl,[bx]
mov ax,4c00h
int 21h
abc ends
end startp
