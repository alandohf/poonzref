;check point 13.2
;main
; int 是如何执行的？
; 1.取得中断类型码，通过 int n 参数提供
; 2.标志寄存器入栈，IF=0，tf=0 因为已经进入了中断，所以置0，屏蔽其他中断，防止干扰。tf=0 是让处理器*正常执行*中断例程*里的各条指令。
; 3.cs,ip 入栈-- 保护现场
; 4.(ip)=(n*4),(cs)=(n*4+2)  -- 把cs：ip 指向中断例程的位置。n为中断编号

; iret 如何执行？
; iret 是 int 的逆操作：
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
	int 7ch ;功能相当于：jmp near ptr s
ok: 
	mov ax,4c00h
	int 21h
	
code ends
end start
