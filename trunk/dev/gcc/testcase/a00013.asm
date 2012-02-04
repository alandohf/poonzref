;muti segment
assume cs:abc
abc segment
dw 0123h,0456h,0789h,0abch,0defh,0fedh,0cbah,0987h
;startp:
mov ax,0
mov cx,8
mov bx,0

s:
add ax,cs:[bx]
add bx,2
loop s 
mov ax,4c00h
int 21h
abc ends
end
;end startp
;d20:0 ff
;dffff:0 ff
