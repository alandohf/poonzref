      .386
      .model flat, stdcall
      option casemap :none   ; case sensitive

; include 	windows.inc
; include 	user32.inc
; includelib 	user32.lib
; include 	kernel32.inc
; includelib 	kernel32.lib

	.data
szCaption 	db 'myProgramTitle',0
szText 		db 'Hello,World!',0
szHello 	db 'Hello',0dh,0ah
			db 'World',0
szResult 	db 'a',0
wordstr 	dw 'a','b'
;dwordstr 	dd 
	.data?
szBuffer 	db 1024*1024 dup(?)

	.code
start:
		mov eax,offset szCaption
		;mov esi,szCaption;wrong
		mov ebx,[eax]
		;mov ax,wordstr ; mov ax,word ptr ds:[40202b]
		;mov ebx,dwordstr
		
	end start
