;9.3
;����Ҫע��,cx���Լ�1�������cx=1,��ִֻ��һ�Σ���,��ִ�е�loop s ʱ������cx���� s�������Ƿ�ִ��.
;���cx=0����ôs������Ҳִ�У�������loop sǰ�ȼ�1����ôcx����ԶС��1��ִ�е�cxԽ��Ϊֹ
;����loop s ǰ����Ҫ���ж�cx�Ƿ�Ϊ0��
assume cs:code
stack segment
db 0ffffh dup(0)
stack ends

code segment
start:
       mov cx,0
	   s: 
	   mov ax,cx
	   add ax,1
	   push ax
	   loop s

		mov ax,4c00h
		int 21h
code ends
end start
