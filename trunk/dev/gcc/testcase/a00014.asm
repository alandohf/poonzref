;将数据入栈
;声明栈空间
;purpose:翻转字存放的顺序

assume cs:abc
abc segment
dw 1200h,5634h,9A78h,0debch,0dcfeh,98bah,5476h,1032h
dw 0,0,0,0,0,0,0,0
startp:
mov ax,cs
mov ss,ax
mov sp,32
;
mov bx,0
mov cx,8
s1:
push cs:[bx]
add bx,2
loop s1
;
mov bx,0
mov cx,8
s2:
pop cs:[bx]
add bx,2
loop s2


mov ax,4c00h
int 21h
abc ends
end startp
