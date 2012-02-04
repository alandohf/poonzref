assume cs:abc
abc segment
startp:
mov ax,0
mov cx,123
s:
add ax,236
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

;debug:
;将ax值保存到内存ds:0中来查看运算结果
