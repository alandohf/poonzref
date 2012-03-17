      .386
      .model flat, stdcall
      option casemap :none   ; case sensitive

include 	windows.inc
include 	user32.inc
includelib 	user32.lib
include 	kernel32.inc
includelib 	kernel32.lib

	.data
szCaption 	db 'myProgramTitle',0
szText 		db 'Hello,World!',0
;szBuffer1 db 1024*1024 dup(0)
szHello db 'Hello',0dh,0ah
		db 'World',0
szResult db 'a',0
;	.data?
;szBuffer db 1024*1024 dup(?)
	.code
;mov bl,sizeof szResult
;add byte ptr [szResult],bl
;mov byte ptr [szResult],bl
start:
	invoke MessageBox,NULL,offset szHello,offset szResult,MB_YESNO
;	invoke MessageBox,NULL,offset szText,offset szCaption,MB_YESNO
	invoke ExitProcess,NULL
	end start
