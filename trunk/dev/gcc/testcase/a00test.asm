;the source file for code test
;cf �����޷�������������
;of ���ڷ�������������
assume cs:code,ds:data

data segment
dw 'AB'
data ends

code segment
start:
		;mov ax,00020h
		; mov cx,00002h
		;div cx
		
		;mov ax,1234h
		;mov al,ah
		; nop
		; ��λ
		;mov al,98h
		;add al,al
		;��λ
		;mov al,97h
		;mov bl,98h
		;sub al,bl ;al - bl -> al
		; sub bl,al ; bl - al -> bl
		;test overflow 1
		; mov al,10001000b
		; mov bl,11110000b
		; add al,bl
		;test overflow 2
		; mov al,01100010b
		; add al,01100011b

		; mov al,98h ;����д��AX=0098h;�������Ϊ�޷��ŵ�152d;������з��ţ���������Ϊ-104d��
		; mov bl,98h
		; add al,bl
				; !!!!!�ȿ��Կ���Ϊ�޷��ŵĽ�λ��Ҳ�������Ϊ�з��ţ������������

		; mov al,78h ;�Ա�98h��78h = 120d ��û�г���127d,����Ĭ��al��Ϊ*�з���*���洢�����ӷ�ʱ���ͻ�����������ǽ�λ��
		; mov bl,78h
		; add al,bl
		;test default flag bits values
		;pushf
		
		; test divide overflow
		;mov ax,1000h
		;mov bl,1h
		;div bl
		
		;test int 
		; mov ax,0b800h
		; mov es,ax
		; mov byte ptr es:[12*160+40*2],'!'
		
		;int 0
		
		;test int 7ch a00064
		;int 7ch
		;test assume ds:data
		; mov ax,data
		; mov ds,ax
		mov ax,ds:[0]
		
		
retp:
		mov ax,4c00h
		int 21h

code ends
end start

