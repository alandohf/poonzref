;我们的启动程序实现很简单的功能，在屏幕中央打印一行字符串即可
[BITS 16]
org 07c00h ;org指令明确告诉编译器我程序的段地址是7C00h，而不是原来的0000
    ;int汇编指令 “int 10h”调用bois里的中断程序：显示字符串
jmp main
gdt_table_start:
gdt_null:
  dd 0h
  dd 0h    ;Intel规定段描述符表的第一个表项必须为0
 gdt_data_addr     equ   $-gdt_table_start
 gdt_data:
  dw 07FFh         ;段界限
      dw 0h           ;段基地址0~18位
      db 0h           ;段基地址19~23位
      db 10010010b    ;段描述符的第6个字节属性（数据段可读可写）
      db 11000000b    ;段描述符的第7个字节属性
      db 0            ;段描述符的最后一个字节也就是段基地址的第二部分
  gdt_video_addr    equ   $-gdt_table_start
  gdt_video:            ;用来描述显存地址空间的段描述符
    dw     0FFh       ;显存段界限就是1M
    dw     8000h     
    db     0Bh
    db     10010010b
    db     11000000b
    db     0
    
 gdt_code_addr     equ   $-gdt_table_start
 gdt_code:
    dw 07FFh         ;段界限(保持不变)
    dw 1h             ;段基地址0~18位                                   不同
    db 80h            ;段基地址19~23位                                  不同
    db 10011010b      ;段描述符的第6个字节属性(代码段可读可执行)          不同
    db 11000000b      ;段描述符的第7个字节属性
    db 0              ;段基地址的第二部分
gdt_table_end:
 gdtr_addr:
  dw gdt_table_end-gdt_table_start-1  ; 段描述符表长度
  dd gdt_table_start   ; 段描述符表基地址
 ;A20地址线问题
main:
  xor eax,eax
  add eax,data_32
  mov word [gdt_data+2],ax
  shr eax,16
  mov byte [gdt_data+4],al
  mov byte [gdt_data+7],ah
 
  xor eax,eax
  add eax,code_32
  mov word [gdt_code+2],ax
  shr eax,16
  mov byte [gdt_code+4],al
  mov byte [gdt_code+7],ah
  ;初始化代码段描述符的基地址
 
 cli
 lgdt  [gdtr_addr]                          ;让CPU读取gdtr_addr所指向内存内容保存到GDT内存当中
 enable_a20:
   in  al,92h
   or  al,00000010b
   out 92h,al
 
 ;设置cr0寄存器第一位为1
 mov eax,cr0
      or  eax,1
      mov cr0,eax
 ;跳转到保护模式中
 jmp gdt_code_addr:0
[BITS 32]
 ;保护模式的功能就是屏幕中央打印hello world
 data_32:
   db "hello world"
 code_32:
   mov ax,gdt_data_addr
   mov ds,ax
   mov ax,gdt_video_addr
   mov gs,ax
 
   mov cx,11   ;显示的字符串长度
   mov edi,(80*10+12)*2   ;在屏幕中央显示
   mov bx,0
   mov ah,0ch 
 s:mov al,[ds:bx]
   mov [gs:edi],al
   mov [gs:edi+1],ah
   inc bx
   add edi,2
   loop s
   jmp $
   times 510-($-$$) db 0 
   dw 0aa55h

