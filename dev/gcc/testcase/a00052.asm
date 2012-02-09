;把数值用字符显示
assume cs:code

stack segment
dw 32 dup(0)
stack ends


data segment
db 16 dup(0)
data ends


code segment
start:
		mov ax,stack
		mov ss,ax
		mov sp,0040h
		mov ax,12345 ;317A; 317a/0a = 4f2 ~ 6
		mov bx,data
		mov ds,bx
		mov si,0
		mov di,0
		
		push si
		
		call d2c
        ;nop

revert_str:	
;转换成可打印字符并入栈
			pop si
			inc di
			mov cx,di
	revert_push:
			mov dx,ds:[si]
			add dx,30h
			push dx
			inc si
			loop revert_push
			
			mov cx,di
			mov si,0
	revert_pop:
			pop dx
			mov ds:[si],dl
			inc si
			loop revert_pop
	add0:
	mov dl,0
	mov ds:[si],dl
;;; rev_push:
;;;   mov cl,ds:[si]
;;;   mov ch,0
;;;   jcxz next
;;;   add cx,30h
;;;   push cx
;;;   inc si
;;;   jmp short rev_push
;;; 
;;; next:
;;;   mov si,0
;;; rev_pop:
;;;	   pop cx
;;;		 jcxz retp  
;;;	   mov ds:[si],cx
;;;	   inc si
;;;	   jmp short rev_pop
;;; 
 ; 调用show_str		
 call_showstr:
 		mov ax,data
 		mov ds,ax
 		mov dh,7  ;row index
 		mov dl,2  ;col index
 		mov cl,0cah  ;color value
 		mov si,0  ;data adress index
 		call show_str

call retp
;########################################################################################
d2c:
;功能：求一个整数的余数
;输出:1.把余数写入内存;返回di,为最后一个余数的偏移地址；di+1 为余数的个数
;
		mov cx,000ah ;设置除数
		;mov ch,0		
		call divdw;ax 商;cx余数
		mov dx,cx
		mov cx,ax
		jcxz d2cret
		mov ds:[di],dl ;保存余数;商只用作判断，不用保存
		mov dx,0
		add di,1
		jmp d2c
d2cret: 
		mov ds:[di],dl ;保存余数;商只用作判断，不用保存
		ret ;d2c
		
divdw:
	   push ax	   ;作为商数的高位
	   mov ax,dx
	   mov dx,0
	   div cx ;get int(h/n) & rem(h/n)
	   pop bx ;把低位取出来
	   push ax ;商;余数dx直接做下次除法的高位
	   mov ax,bx   ;取出低位,直接放在ax做低位
	   div cx
	   mov cx,dx;保存余数
	   pop dx ;恢复商数的高位到dx
	   ret ;divdw return


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
