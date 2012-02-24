link=c:\masm32\bin\link.exe
ml=c:\masm32\bin\ml.exe
OUTPUTDIR=C:\ccoutput
#
LINK_FLAG = /SUBSYSTEM:WINDOWS
ML_FLAG = /c /coff /nologo
#
NAME = t00001
OBJS = $(NAME).obj


$(NAME).exe: $(OBJS)
	$(link) $(LINK_FLAG) $(OBJS) /out:$(OUTPUTDIR)\$(NAME).exe
.asm.obj:
	$(ml) $(ML_FLAG) $<
clean:
	rm *.obj
