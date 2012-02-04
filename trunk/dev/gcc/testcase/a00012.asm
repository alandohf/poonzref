; test invaid access of memory
; 0:200h ~ 0:2ffh
; 0020:0000h~ 0020:00ffh
assume cs:abc
abc segment
startp:
mov bx,0
mov cx,02ffh
s:
mov ax,0ffffh
mov ds,ax
mov dl,ds:[bx]
mov ax,0020h
mov ds,ax
mov ds:[bx],dl
inc bx
loop s
mov ax,4c00h
int 21h
abc ends
end startp
;d20:0 ff
;dffff:0 ff
