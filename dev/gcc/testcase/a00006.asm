assume cs:abc
abc segment
startp:
mov ax,2
; 12-1 is ok
mov cx,12-1
;mov cx,11
s:
add ax,ax
loop s
mov ax,4c00h
int 21h
abc ends
;end s
end startp
;end