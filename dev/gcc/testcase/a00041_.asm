
;exp 9
;b8000:bffff ~ b800:0 7fff; 所以是0-7fffh ,即8000h byte = 32 k byte = 4kb * 8 = 4*1024b*8 = 的显存空间
;第一屏:0~0fffh
;第一行:80*2b=160byte
;25行占用：25*160byte = 4000b<4kb
;所以每行用160b

;80*25*256 = 7d000h ;i.e. 80*25*100h = 7d000h

assume cs:code

code segment
start:
mov ax,0b800h
mov es,ax
mov bx,0
mov al,41h
mov es:[bx],al

mov di,1
mov ah,02h
mov es:[di],ah
push es:[bx]
pop dx
return:
		mov ax,4c00h
		int 21h
code ends
end start
