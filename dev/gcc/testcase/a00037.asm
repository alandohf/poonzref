;9.3
;����Ҫע��,cx���Լ�1�������cx=1,��ִֻ��һ�Σ���
assume cs:code
code segment
start:
        mov ax,0b5bh
        mov ds,ax
        mov bx,40h
        s:
                mov cl,[bx]
                mov ch,0
                inc cx    ;����ָ��Ϊ��ĿҪ��ȫ��ָ��
                inc bx
        loop s
       
        ok:
                dec bx
                mov dx,bx
                mov ax,4c00h
                int 21h
code ends
end start
