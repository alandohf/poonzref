;���ǵ���������ʵ�ֺܼ򵥵Ĺ��ܣ�����Ļ�����ӡһ���ַ�������
org 07c00h ;orgָ����ȷ���߱������ҳ���Ķε�ַ��7C00h��������ԭ����0000
		   ; 7c00h ���Ƕε�ַ����ƫ�Ƶ�ַ���ε�ַ��0.so�� org 07c00h = org 0:7c00h
;int���ָ�� ��int 10h������bois����жϳ�����ʾ�ַ���
 mov ax,cs
 mov es,ax
 mov bp,msgstr  ;es:bp ָ������ݾ�������Ҫ��ʾ���ַ�����ַ��
 
 mov cx,24   ;��ʾ���ַ�������
 mov dh,12   ;��ʾ���к�
 mov dl,36   ;��ʾ���к�
 mov bh,0    ;��ʾ��ҳ��
 mov al,1    ;��ʾ���Ǵ��ṹ
 mov bl,0ch  ;��ʾ���ַ�����
 
 mov ah,13h  ;��ȷ����13h�ӳ���
int 10h
msgstr: db "displaying a string on screen!"
 times 510-($-$$) db 0  ;�ظ�n��ÿ�����ֵΪ0
 db 55h
 db 0aah
 jmp $   ;������ת����ǰλ�ã��Ǹ���ѭ��