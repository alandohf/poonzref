assume cs:abc
abc segment
startp:
mov ax,ffff
mov ds,ax
mov bx,6h
mov ax,[bx]
mov cx,3-1
s:
add ax,ax
loop s
mov dx,ax
mov ax,4c00h
int 21h
abc ends
end startp

