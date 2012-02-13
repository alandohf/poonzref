;取得cmos ram 中的bcd日期 ， 并转换成可显示的10进制形式。
assume cs:code

code segment
start:
		mov al,8
		out 70h,al ;向端口写入地址
		
		in al ,71h ;从端口获取数据
		
		mov ah,al
		mov cl,4
		shr ah,cl	;取月份的10位
		and al,00001111b ;取月份的个位
		add al,30h
		add ah,30h

		
	
mov ax,4c00h
int 21h
			
code ends
end start
