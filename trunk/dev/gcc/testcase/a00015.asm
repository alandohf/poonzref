;��������ջ
;����ջ�ռ�
;purpose:��ת�ִ�ŵ�˳��;����ջ�����ݶνṹ

assume cs:scode,ds:sdata,ss:sstack;

sdata segment
dw 1200h,5634h,9A78h,0debch,0dcfeh,98bah,5476h,1032h
sdata ends

sstack segment
dw 0,0,0,0,0,0,0,0
sstack ends

scode segment
startp:
mov ax,sstack
mov ss,ax
mov ax,sdata
mov ds,ax
mov sp,16
;
mov bx,0
mov cx,8
s1:
push [bx]
add bx,2
loop s1
;
mov bx,0
mov cx,8
s2:
pop [bx]
add bx,2
loop s2


mov ax,4c00h
int 21h
scode ends
end startp
