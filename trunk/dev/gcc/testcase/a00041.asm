;ע�Ȿ������win7ִ���޷��õ���ɫ��Ҫ����������ܣ��õ���win98 dos ��������ִ�У�
assume cs:code
stack segment
dw 8 dup(0)
stack ends

data segment
db 'welcome to masm!';����Ϊ16 (0,15��
db 02h,24h,71h
;db 0cah,42h,33h ;�����ֽ�,3��  ��16,18)
data ends

code segment
start:
init:
	mov ax,stack
	mov ss,ax
	mov sp,10h
	mov ax,data
	mov ds,ax
	mov ax,0b800h
	mov es,ax; �Դ���׵�ַ
	;mov bx,0 ; ѭ�����ӣ�����У�����Ϊ160�����ֽڣ�;��ʼ��bx 
	mov bx,160*11 ; ѭ�����ӣ�����У�����Ϊ160�����ֽڣ�;��ʼ��bx 
	mov cx,3 ; ѭ�����ӣ���¼��д�������
    mov dx,0 ;��ʱ����;����������ɫ��si

writep:
		push cx
		mov si,0 ; ���� welcome...�ַ�����ÿ���ֽ�		
		mov di,0 ;����д��Ŀ���ڴ���ַ�ƫ����
		mov cx,16
		;����ɫ���Լ���Ĵ���
		push si;����siȡds�е���ɫ����ֵ
		mov si,dx
		mov ah,ds:10h[si]
		add si,1
		mov dx,si
		pop si
	printl:			
			mov al,ds:0[si]
			;mov ah,ds:[16];��һ��
			;mov ah,0cah
			;mov es: [bx+di] ,al ;д���Դ�
			;mov es:1[bx+di] ,ah ;д���Դ�
			;����ƫ�Ƶ�ַ 
			mov es: 40h[bx+di] ,al ;д���Դ�
			mov es:41h[bx+di] ,ah ;д���Դ�
			inc si
			add di,2
			loop printl
			pop cx
			add bx,160
loop writep

return:
		mov ax,4c00h
		int 21h
code ends
end start

;exp 9
;b8000:bffff ~ b800:0 7fff; ������0-7fffh ,��8000h byte = 32 k byte = 4kb * 8 = 4*1024b*8 = ���Դ�ռ�
;��һ��:0~0fffh
;��һ��:80*2b=160byte
;25��ռ�ã�25*160byte = 4000b<4kb
;����ÿ����160b

;80*25*256 = 7d000h ;i.e. 80*25*100h = 7d000h
