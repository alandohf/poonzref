;http://www.programmersheaven.com/mb/x86_asm/275460/275460/org-100h--org-7c00h-/
;hmm,ive got the same problem some years ago.unfortunatley i cant find the source.i think ive compiled the code ;to an .exe file which writes 512 bytes to the bootsector or an image-file.here some untested pseudo-code.its ;been a while since im been working with this,hope it works 

.CODE
Start PROC
  call WriteBootSec
  mov  ah,4ch
  int  21h
Start ENDP

WriteBootsec PROC
...
 ret
WriteBootSec ENDP

ORG 7C00h
; place your boot-sector-code here
...
; place your data here
...
ORG 7DFEh
 dw 0AA55h   ; boot-sector-id
 