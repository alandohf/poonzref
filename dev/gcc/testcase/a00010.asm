; usage of ds:[bx] and loop to set memory 
assume cs:abc
abc segment
startp:
mov ax,0ffffh
mov ds,ax
mov cx,20h
mov dx,0
mov bx,0
s:
;mov al,ds:[bx]
mov al,65
mov ah,0
mov ds:[bx],ax
inc bx
loop s
;mov ax,4321h
;mov ds:[100h],ax
;mov ds:[100h],dx
mov ax,4c00h
int 21h
abc ends
end startp
