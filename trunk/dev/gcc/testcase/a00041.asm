;注意本程序在win7执行无法得到颜色，要在虚拟机中跑！用的是win98 dos 引导盘来执行！
assume cs:code
stack segment
dw 8 dup(0)
stack ends

data segment
db 'welcome to masm!';长度为16 (0,15）
db 02h,24h,71h
;db 0cah,42h,33h ;单个字节,3个  （16,18)
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
	mov es,ax; 显存段首地址
	;mov bx,0 ; 循环因子，标记行，步长为160（个字节）;初始化bx 
	mov bx,160*11 ; 循环因子，标记行，步长为160（个字节）;初始化bx 
	mov cx,3 ; 循环因子，记录行写入次数；
    mov dx,0 ;临时变量;保存索引颜色的si

writep:
		push cx
		mov si,0 ; 索引 welcome...字符串中每个字节		
		mov di,0 ;索引写入目标内存的字符偏移量
		mov cx,16
		;把颜色属性加入寄存器
		push si;借用si取ds中的颜色属性值
		mov si,dx
		mov ah,ds:10h[si]
		add si,1
		mov dx,si
		pop si
	printl:			
			mov al,ds:0[si]
			;mov ah,ds:[16];第一行
			;mov ah,0cah
			;mov es: [bx+di] ,al ;写入显存
			;mov es:1[bx+di] ,ah ;写入显存
			;加入偏移地址 
			mov es: 40h[bx+di] ,al ;写入显存
			mov es:41h[bx+di] ,ah ;写入显存
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
;b8000:bffff ~ b800:0 7fff; 所以是0-7fffh ,即8000h byte = 32 k byte = 4kb * 8 = 4*1024b*8 = 的显存空间
;第一屏:0~0fffh
;第一行:80*2b=160byte
;25行占用：25*160byte = 4000b<4kb
;所以每行用160b

;80*25*256 = 7d000h ;i.e. 80*25*100h = 7d000h
