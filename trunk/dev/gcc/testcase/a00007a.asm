assume cs:abc
abc segment
startp:
mov ax,0
mov cx,236
s:
add ax,123
loop s
mov dx,ax
mov bx,0
mov [bx],dx
mov ax,4c00h
int 21h
abc ends
;end s
end startp
;end