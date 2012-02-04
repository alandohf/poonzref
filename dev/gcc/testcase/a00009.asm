; usage of ds:[bx] and loop 
assume cs:abc
abc segment
startp:
mov ax,0ffffh
mov ds,ax
mov cx,12
mov dx,0
mov bx,0
s:
;mov al,ds:[bx]
mov al,[bx]
mov ah,0
add dx,ax
inc bx
loop s
mov ax,4321h
mov ds:[100h],ax
mov ds:[100h],dx
mov ax,4c00h
int 21h
abc ends
end startp
