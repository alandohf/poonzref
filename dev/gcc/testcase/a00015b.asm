;��������ջ
;����ջ�ռ�
;purpose:��ת�ִ�ŵ�˳��;����ջ�����ݶνṹ
;���ò�ͬ����ڵ�ַ����startp���õ�stack�У�,�鿴������
assume cs:code,ds:data,ss:stack

data segment
dw 1200h,5634h,9A78h,0debch,0dcfeh,98bah,5476h,1032h
data ends

code segment
mov ax,stack
mov ss,ax
mov ax,data
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
code ends

stack segment
startp:
dw 0,0,0,0,0,0,0,0
stack ends
end startp
