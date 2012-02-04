assume cs:abc
abc segment
startp:
mov ax,0123h
add bx,0456h
add ax,bx
add ax,ax
mov ax,4c00h
int 21h
abc ends
end startp
