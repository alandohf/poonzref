;中断处理程序替换
;1.注意错误提示信息的存放
;2.注意合理设置显存地址
;3.注意代码偏移量的设置
;4.注意中断向量表的覆盖

;TF（Trap Flag）陷阱标志：当TF被设置位1时，CPU进入单步模式，所谓单步模式就是CPU在每执行一步指令后都产生一个单步中断。主要用于程序的调试。
;8086/8088中没有专门用来置位和清零TF的命令，需要用其他办法。　　
;IF（Interrupt Flag）中断标志：决定CPU是否
;响应外部可屏蔽中断请求。TF为1时，CPU允许响应外部的可屏蔽中断请求。　

assume cs:code

code segment
start:
			
		mov ax,cs ;代码拷贝
		mov ds,ax
		mov si,offset do0
		mov ax,0
		mov es,ax
		mov di,200h
		mov cx,offset do0end - offset do0
		cld
		rep movsb ; ds->es
		;set interupt table
		mov ax,0
		mov es,ax
		mov word ptr es:[0*4],200h
		mov word ptr es:2[0*4],0
		
		mov ax,4c00h
		int 21h

do0:
		jmp short do0start
		db 'A divide error occours!'
do0start:
		mov ax,cs
		mov ds,ax
		mov si,202h
		mov ax,0b800h
		mov es,ax
		mov di,12*160
		
		mov cx,23
	s:  mov al,[si]
		mov es:[di],al
		inc si
		mov al,0cah
		mov es:1[di],al
		add di,2
		loop s
		mov ax,4c00h
		int 21h
do0end:
		nop

code ends
end start
