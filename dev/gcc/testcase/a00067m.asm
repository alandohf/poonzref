;check point 13.2
;main
; int �����ִ�еģ�
; 1.ȡ���ж������룬ͨ�� int n �����ṩ
; 2.��־�Ĵ�����ջ��IF=0��tf=0 ��Ϊ�Ѿ��������жϣ�������0�����������жϣ���ֹ���š�tf=0 ���ô�����*����ִ��*�ж�����*��ĸ���ָ�
; 3.cs,ip ��ջ-- �����ֳ�
; 4.(ip)=(n*4),(cs)=(n*4+2)  -- ��cs��ip ָ���ж����̵�λ�á�nΪ�жϱ��

; iret ���ִ�У�
; iret �� int ���������
; pop ip
; pop cs
; popf


assume cs:code


data segment
db 'conversation',0
data ends


code segment
start:
	
	mov ax,data
	mov ds,ax
	mov si,0
	mov ax,0b800h
	mov es ,ax
	mov di,12*160
s:	
	cmp byte ptr [si],0
	je ok
	mov al,[si]
	mov es:[di],al
	inc si
	add di,2
	mov bx,offset s - offset ok
	int 7ch ;�����൱�ڣ�jmp near ptr s
ok: 
	mov ax,4c00h
	int 21h
	
code ends
end start
