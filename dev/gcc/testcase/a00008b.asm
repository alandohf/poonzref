assume cs:abc
abc segment
startp:
mov ax,0ffffh
mov ds,ax
mov bx,06h
mov cx,3
mov ax,0;
mov dx,0
mov al,[bx]
mov ah,0
s:
add dx,ax
loop s
mov ax,4c00h
int 21h
abc ends
end startp
