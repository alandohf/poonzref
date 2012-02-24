;我们的启动程序实现很简单的功能，在屏幕中央打印一行字符串即可
org 07c00h ;org指令明确告诉编译器我程序的段地址是7C00h，而不是原来的0000
		   ; 7c00h 不是段地址，是偏移地址！段地址是0.so： org 07c00h = org 0:7c00h
;int汇编指令 “int 10h”调用bois里的中断程序：显示字符串
 mov ax,cs
 mov es,ax
 mov bp,msgstr  ;es:bp 指向的内容就是我们要显示的字符串地址了
 
 mov cx,24   ;显示的字符串长度
 mov dh,12   ;显示的行号
 mov dl,36   ;显示的列号
 mov bh,0    ;显示的页数
 mov al,1    ;显示的是串结构
 mov bl,0ch  ;显示的字符属性
 
 mov ah,13h  ;明确调用13h子程序
int 10h
msgstr: db "displaying a string on screen!"
 times 510-($-$$) db 0  ;重复n次每次填充值为0
 db 55h
 db 0aah
 jmp $   ;不断跳转到当前位置，是个死循环
