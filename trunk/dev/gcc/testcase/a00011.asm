; test invaid access of memory
assume cs:abc
abc segment
startp:
mov ax,0
mov ds,ax
mov ds:[20h],ax

mov ax,4c00h
int 21h
abc ends
end startp
