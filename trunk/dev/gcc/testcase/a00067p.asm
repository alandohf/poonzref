;check point 13.2
;procedure
assume cs:code

code segment
start:
	
	mov ax,cs
	mov ds,ax
	mov ax,0
	mov es,ax
	mov si ,offset toupper
	mov di,0200h
	mov cx , offset end_toupper - offset toupper
	cld ; ��©��
	rep movsb ;rep , not dup
	
	;setup
	mov ax,0
	mov es,ax
	mov word ptr es:[7ch*4],200h ;int 7ch ; ע����word ptr!!!
	mov word ptr es:2[7ch*4],0 ; h �Ǳ���ģ������c
	
mov ax,4c00h
int 21h
		
toupper:
	
		push bp
		mov bp,sp
		;dec cx��������; jmp ��ͬ��loop������Ҫѭ������
		;jcxz lpret ; jmp ��ͬ��loop������Ҫѭ�����ӡ���i make it ! yeah!
		add [bp+2],bx
lpret:
		pop bp
		iret ;ע��iret �� int �ǳɶ�ִ�еģ�ִ����һ��int����Ҫ��Ӧִ��һ��iret!
		
;mov ax,4c00h
;int 21h
		
end_toupper:
			nop
			
code ends
end start
