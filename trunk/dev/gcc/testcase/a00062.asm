;int 7ch
assume cs:code

code segment
start:
	
	mov ax,3456;
	int 7ch ; 7ch ����ʵ�ּ���ƽ������
	
	add ax,ax
	adc dx,dx
	
	mov ax,4c00h
	int 21h
	
code ends
end start
