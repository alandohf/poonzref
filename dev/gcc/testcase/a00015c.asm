;1.end [tag] ��ǩҪ���ڳ������tag�����λ�ÿ�����endǰ���κ�һ���ζ����С�
;2.���ֻ��end��û��[tag],�ε�λ�ð��Ų���Ӱ�����ı��룬����ִ��˳��ͻᰴ��д��˳������������û��ָ�����ʱ��Ҫ�Ѵ���η�ǰ�档
;3.û��end�ĳ����Ǵ����
;4.��2���ȶ���Ķ�ռ�ݵ͵�ַ�������ռ�ݸߵ�ַ�����ַ��䷽ʽ֤����2��.
assume cs:code,ds:data,ss:stack


code segment

	mov ax,stack
	mov ss,ax
	mov ax,data
	mov ds,ax
	mov sp,16
	;
	mov bx,0
	mov cx,8
	s1:
	push [bx]
	add bx,2
	loop s1
	;
	mov bx,0
	mov cx,8
	s2:
	pop [bx]
	add bx,2
	loop s2


	mov ax,4c00h
	int 21h
code ends




data segment
	dw 1200h,5634h,9A78h,0debch,0dcfeh,98bah,5476h,1032h
data ends


stack segment
	dw 0,0,0,0,0,0,0,0
stack ends




end 
