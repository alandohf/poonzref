;���ǵ���������ʵ�ֺܼ򵥵Ĺ��ܣ�����Ļ�����ӡһ���ַ�������
[BITS 16]
org 07c00h ;orgָ����ȷ���߱������ҳ���Ķε�ַ��7C00h��������ԭ����0000
    ;int���ָ�� ��int 10h������bois����жϳ�����ʾ�ַ���
jmp main
gdt_table_start:
gdt_null:
  dd 0h
  dd 0h    ;Intel�涨����������ĵ�һ���������Ϊ0
 gdt_data_addr     equ   $-gdt_table_start
 gdt_data:
  dw 07FFh         ;�ν���
      dw 0h           ;�λ���ַ0~18λ
      db 0h           ;�λ���ַ19~23λ
      db 10010010b    ;���������ĵ�6���ֽ����ԣ����ݶοɶ���д��
      db 11000000b    ;���������ĵ�7���ֽ�����
      db 0            ;�������������һ���ֽ�Ҳ���Ƕλ���ַ�ĵڶ�����
  gdt_video_addr    equ   $-gdt_table_start
  gdt_video:            ;���������Դ��ַ�ռ�Ķ�������
    dw     0FFh       ;�Դ�ν��޾���1M
    dw     8000h     
    db     0Bh
    db     10010010b
    db     11000000b
    db     0
    
 gdt_code_addr     equ   $-gdt_table_start
 gdt_code:
    dw 07FFh         ;�ν���(���ֲ���)
    dw 1h             ;�λ���ַ0~18λ                                   ��ͬ
    db 80h            ;�λ���ַ19~23λ                                  ��ͬ
    db 10011010b      ;���������ĵ�6���ֽ�����(����οɶ���ִ��)          ��ͬ
    db 11000000b      ;���������ĵ�7���ֽ�����
    db 0              ;�λ���ַ�ĵڶ�����
gdt_table_end:
 gdtr_addr:
  dw gdt_table_end-gdt_table_start-1  ; ������������
  dd gdt_table_start   ; �������������ַ
 ;A20��ַ������
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
  ;��ʼ��������������Ļ���ַ
 
 cli
 lgdt  [gdtr_addr]                          ;��CPU��ȡgdtr_addr��ָ���ڴ����ݱ��浽GDT�ڴ浱��
 enable_a20:
   in  al,92h
   or  al,00000010b
   out 92h,al
 
 ;����cr0�Ĵ�����һλΪ1
 mov eax,cr0
      or  eax,1
      mov cr0,eax
 ;��ת������ģʽ��
 jmp gdt_code_addr:0
[BITS 32]
 ;����ģʽ�Ĺ��ܾ�����Ļ�����ӡhello world
 data_32:
   db "hello world"
 code_32:
   mov ax,gdt_data_addr
   mov ds,ax
   mov ax,gdt_video_addr
   mov gs,ax
 
   mov cx,11   ;��ʾ���ַ�������
   mov edi,(80*10+12)*2   ;����Ļ������ʾ
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

