;ת�򱣻�ģʽ��̺���Ҫ��һ���ǣ����ʵ�ַ���ǲ��öμĴ�����ƫ�Ƶ�ַ�ķ�ʽ���ʣ����ǣ��μĴ�����ŵĲ����Ƕε�ַ�����Ƕ�ѡ���ӣ�Ҳ�������ݶ�/������ڶ����������е�λ�ã������������ڶ�ѡ���ӣ�ƫ�Ƶ�ַ����ôת�������ַ�ģ����ǲ��ù��ġ�

;���岽�裺
;1.�������������
;2.���б�Ҫ���޸Ķ������������
;3.����ж�������
;4.���ض��������Ĵ��� lgdt
;5.��a20,�����л�������ģʽ����Ĳ��衣Ϊ����80386���ϵ�cpu����ʵģʽ
;6.�޸�cr0 peλ����cpuҪ���뱣��ģʽ
;7.��ת�������ִ�д���
;8.���ݶε�λ���ǿ���ѡ���
[BITS 16]
org 07c00h ;gcc����ʱ��Ҫ���ε�
;jmp main
  
 ;A20��ַ������
main:
  xor eax,eax
  add eax,data_32
  mov word [gdt_data+2],ax
  shr eax,16
  mov byte [gdt_data+4],al
  mov byte [gdt_data+7],ah
 ;���ϳ�ʼ�����ݶ���������ĵ�һ����¼�Ļ���ַ�������������ݶ�"hello world"
  xor eax,eax
  add eax,code_32
  mov word [gdt_code+2],ax
  shr eax,16
  mov byte [gdt_code+4],al
  mov byte [gdt_code+7],ah
  ;���ϳ�ʼ��������������Ļ���ַ
 
 cli ;����ж�������
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
 jmp gdt_code_rltvaddr:0
[BITS 32]
 ;����ģʽ�Ĺ��ܾ�����Ļ�����ӡhello world
 data_32:
   db "hello-world!",0
 code_32:
   mov ax,gdt_data_rltvaddr
   mov ds,ax ;source
   mov ax,gdt_video_rltvaddr
   mov gs,ax ;dest
 ;��Ϊû��bios�жϿ����ˣ�����Ҫ����ԭʼ�ķ��������Դ��д��Ҫ��ʾ���ַ�
   mov edi,(80*10+34)*2   ;����Ļ������ʾ;34�������룬12����
   ;mov edi,0
   mov esi,0    ;����source string
   xor ecx,ecx
   mov ah,0ch  ;������ɫ
   mov cx,12   ;����ѭ��������ʹ���ܹ����ַ����ĳ�����ʾ��һ��Ҫ����ecx
				;(��֤ecx������������Ҫ���õ�ѭ������)�� loop��������ecx,����cx!!
s:mov al, [ds:esi]
   mov [gs:edi],al
   mov [gs:edi+1],ah
   inc esi
   add edi,2
   loop s
jmp $

gdt_table_start:
 gdt_null:
  dd 0h
  dd 0h    ;Intel�涨����������ĵ�һ���������Ϊ0
 gdt_data_rltvaddr     equ   $-gdt_table_start
 gdt_data:
  dw 07FFh         ;�ν���
      dw 0h           ;�λ���ַ0~18λ
      db 0h           ;�λ���ַ19~23λ
      db 10010010b    ;���������ĵ�6���ֽ����ԣ����ݶοɶ���д��
      db 11000000b    ;���������ĵ�7���ֽ�����
      db 0            ;�������������һ���ֽ�Ҳ���Ƕλ���ַ�ĵڶ�����
  gdt_video_rltvaddr    equ   $-gdt_table_start
  gdt_video:            ;���������Դ��ַ�ռ�Ķ�������
    dw     0FFh       ;�Դ�ν��޾���1M
    dw     8000h     
    db     0Bh
    db     10010010b
    db     11000000b
    db     0
    
 gdt_code_rltvaddr     equ   $-gdt_table_start ;����������������������е����λ�ã���ַ��
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

   times 510-($-$$) db 0
   db 55h
   db 0aah
