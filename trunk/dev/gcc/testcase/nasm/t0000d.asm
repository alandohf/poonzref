;使用gdb调试nasm 程序，不过在windows下似乎不行;用objdump可以！！单不太完整；使用-D选项更完整！
;http://www.360doc.com/content/11/0330/20/507289_105963920.shtml
; nasm -f elf t0000d.asm -g -F stabs
; gcc -o t0000d.exe t0000d.o -g

[BITS 16]
;org 07c00h ;gcc调试时需要屏蔽掉
jmp main
gdt_table_start:
 gdt_null:
  dd 0h
  dd 0h    ;Intel规定段描述符表的第一个表项必须为0
 gdt_data_rltvaddr     equ   $-gdt_table_start
 gdt_data:
  dw 07FFh         ;段界限
      dw 0h           ;段基地址0~18位
      db 0h           ;段基地址19~23位
      db 10010010b    ;段描述符的第6个字节属性（数据段可读可写）
      db 11000000b    ;段描述符的第7个字节属性
      db 0            ;段描述符的最后一个字节也就是段基地址的第二部分
  gdt_video_rltvaddr    equ   $-gdt_table_start
  gdt_video:            ;用来描述显存地址空间的段描述符
    dw     0FFh       ;显存段界限就是1M
    dw     8000h     
    db     0Bh
    db     10010010b
    db     11000000b
    db     0
    
 gdt_code_rltvaddr     equ   $-gdt_table_start ;代码段描述符在描述符表中的相对位置（地址）
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
 ;以上初始化数据段描述符表的第一条记录的基地址，用于描述数据段"hello world"
  xor eax,eax
  add eax,code_32
  mov word [gdt_code+2],ax
  shr eax,16
  mov byte [gdt_code+4],al
  mov byte [gdt_code+7],ah
  ;以上初始化代码段描述符的基地址
 
 cli ;清除中断向量表
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
 jmp gdt_code_rltvaddr:0
[BITS 32]
 ;保护模式的功能就是屏幕中央打印hello world
 data_32:
   db "hello world!",0
 code_32:
   mov ax,gdt_data_rltvaddr
   mov ds,ax ;source
   mov ax,gdt_video_rltvaddr
   mov gs,ax ;dest
 ;因为没有bios中断可用了，所以要用最原始的方法，向显存段写入要显示的字符
   mov edi,(80*10+34)*2   ;在屏幕中央显示
   ;mov edi,0
   mov esi,0    ;索引source string
   xor ecx,ecx
   mov ah,0ch  ;设置颜色
   mov cx,12   ;设置循环次数，使得能够按字符串的长度显示。一定要清零ecx
				;(保证ecx里面存的数是你要设置的循环次数)！ loop　检查的是ecx,不是cx!!
s:mov al, [ds:esi]
   mov [gs:edi],al
   mov [gs:edi+1],ah
   inc esi
   add edi,2
   loop s
jmp $
   times 510-($-$$) db 0
   db 55h
   db 0aah
