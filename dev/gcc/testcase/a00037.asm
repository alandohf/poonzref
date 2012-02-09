;9.3
;本题要注意,cx先自减1！！如果cx=1,则只执行一次！！
assume cs:code
code segment
start:
        mov ax,0b5bh
        mov ds,ax
        mov bx,40h
        s:
                mov cl,[bx]
                mov ch,0
                inc cx    ;此条指令为题目要求补全的指令
                inc bx
        loop s
       
        ok:
                dec bx
                mov dx,bx
                mov ax,4c00h
                int 21h
code ends
end start
