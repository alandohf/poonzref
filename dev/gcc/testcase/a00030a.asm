;fishc ʵ��7
;1.���һ�������ڴ�д�����һ���ֵ�ֵ
;2.ds,ss,es�İ����м��ɣ�
assume cs:scode
stack segment
dw 0
stack ends
data segment
;year
	db'1975','1976','1977','1978','1979','1980','1981','1982','1983','1984','1985','1986','1987','1988','1989','1990','1991','1992','1993','1994','1995'
;income
	dd 16,22,382,1356,2390,8000,16000,24486,50065,97479,140417,197514
	dd 345980,590827,803530,1183000,1843000,2759000,3753000,4649000,5937000
;emp number
	dw 3,7,9,13,28,38,130,220,476,778,1001,1442,2258,2793,4037,5635,8226
	dw 11542,14430,15257,17800
data ends
table segment
db 21 dup('year summ ne ?? ')
table ends

scode segment
start:
		mov ax,stack
		mov ss,ax
		
		mov ax,table
		mov es,ax
		
		mov ax,data
		mov ds,ax

		mov bx,0  ;����ƫ����������Ϊ2
		mov si,0 ;����Ϊ4
		mov di,0 ; ����Ϊ10h
		mov cx,21 ;ѭ������
loops:		
		push cx;ѹջ		
		mov cx,ds:0[si]
		mov es:0[di],cx;������
		mov cx,ds:2[si]
		mov es:2[di],cx;������

		mov ax,ds:84[si]   ;ȡ���
		mov dx,ds:86[si]
		mov es:5[di],ax;�����ܶ�
		mov es:7[di],dx;�����ܶ�
		add si,4 ;���Ϊ˫�֣�ÿ��ƫ��4

		mov cx,ds:168[bx]; ȡ��������
		div cx			   ; ����
		mov es:13[di],ax ; ������;��
		mov ax,ds:168[bx];ȡ��������
		mov es:10[di],ax;��������
		mov al,' '
		mov es:4[di],al ;���ո�
		mov es:9[di],al
		mov es:12[di],al
		mov es:15[di],al
		add bx,2
		add di,10h 
pop cx;��ջ
loop loops
		;return
		mov ax,4c00h
		int 21h
	scode ends
end start
