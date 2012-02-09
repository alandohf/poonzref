;注意要计算好段地址，偏移地址
;对低位操作要注意高位是否要置0！
;相比小甲鱼的，他先把si,cx(cl) 压栈。其实如果si,cx用途单一，如dh ，只用来作实参传值到show_str，也可以不压栈。
assume cs:code

data segment
db 'This is a show string program',0
data ends

code segment
start:
		mov ax,data
		mov ds,ax
;设置实际参数的值		
		mov dh,8  ;row index
		mov dl,3  ;col index
		mov cl,02h  ;color value
		mov si,0  ;data adress index
		call show_str
exitp:	call retp
show_str:
;功能:打印data段字符；按特定行列和颜色。
;输入:dh 行;dl 列;cl 颜色；ds:si 数据首地址
		;初始化
		;参数处理:根据row值计算起始段地址
		mov al,0ah ;0a0 = 160/16
		mov ah,0
		mov bl,dh
		mul bl
		add ax,0b800h
		mov es,ax
		;mov bx,0 ;使用si
		;mov di,0
		;参数处理:将col转换成偏移量，计算di的值
		mov al,dl
		mov ah,0
		mov bl,2
		mul bl
		mov di,ax ;参数处理：初始化di；di索引显存偏移
		;参数处理:颜色属性
		mov al,cl  ;处理颜色
		mov ah,0
		;参数处理:处理首地址
		;and si,ffffh
writestr:
		;读取字串写入显存
		mov cl,ds:[si];读取
		mov ch,0
		jcxz show_str_ret
		mov es:[di],cl ;写入
		;mov ax,0cah
		mov es:1[di],ax
		add di,2
		inc si
		jmp short writestr
show_str_ret:
		ret;show_str_ret

		
retp:		
		mov ax,4c00h
		int 21h

code ends
end start
