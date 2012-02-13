Could somebody please explain what GCC is doing for this piece of code? What is it initializing? The original code is:

#include <stdio.h>
int main()
{

}
And it was translated to:

    .file       "test1.c"
    .def        ___main;        .scl    2;      .type   32;     .endef
    .text
.globl _main
    .def        _main;  .scl    2;      .type   32;     .endef
_main:
    pushl       %ebp
    movl        %esp, %ebp
    subl        $8, %esp
    andl        $-16, %esp
    movl        $0, %eax
    addl        $15, %eax
    addl        $15, %eax
    shrl        $4, %eax
    sall        $4, %eax
    movl        %eax, -4(%ebp)
    movl        -4(%ebp), %eax
    call        __alloca
    call        ___main
    leave
    ret
I would be grateful if a compiler/assembly guru got me started by explaining the stack, register and the section initializations. I cant make head or tail out of the code.

EDIT: I am using gcc 3.4.5. and the command line argument is gcc -S test1.c
answer:
It would really help to know what gcc version you are using and what libc. It looks like you have a very old gcc version or a strange platform or both. What's going on is some strangeness with calling conventions. I can tell you a few things:

Save the frame pointer on the stack according to convention:

pushl       %ebp
movl        %esp, %ebp
Make room for stuff at the old end of the frame, and round the stack pointer down to a multiple of 4 (why this is needed I don't know):

subl        $8, %esp
andl        $-16, %esp
Through an insane song and dance, get ready to return 1 from main:

SAL(Shift Arithmetic Left):  算术左移

SAL: 每位左移, 低位补 0,  高位进入CF


例：SAL AX,1

逻辑左移和算术左移有什么区别？
左移是一样的，右移是不同的 
逻辑右移补0，算术右移补最高位
movl        $0, %eax
addl        $15, %eax
addl        $15, %eax
shrl        $4, %eax
sall        $4, %eax
movl        %eax, -4(%ebp)
movl        -4(%ebp), %eax
Recover any memory allocated with alloca (GNU-ism):

call        __alloca
Announce to libc that main is exiting (more GNU-ism):

call        ___main
Restore the frame and stack pointers:

leave
Return:

ret
Here's what happens when I compile the very same source code with gcc 4.3 on Debian Linux:

        .file   "main.c"
        .text
        .p2align 4,,15
.globl main
        .type   main, @function
main:
        leal    4(%esp), %ecx
        andl    $-16, %esp
        pushl   -4(%ecx)
        pushl   %ebp
        movl    %esp, %ebp
        pushl   %ecx
        popl    %ecx
        popl    %ebp
        leal    -4(%ecx), %esp
        ret
        .size   main, .-main
        .ident  "GCC: (Debian 4.3.2-1.1) 4.3.2"
        .section        .note.GNU-stack,"",@progbits
And I break it down this way:

Tell the debugger and other tools the source file:

        .file   "main.c"
Code goes in the text section:

        .text
Beats me:

        .p2align 4,,15
main is an exported function:

.globl main
        .type   main, @function
main's entry point:

main:
Grab the return address, align the stack on a 4-byte address, and save the return address again (why I can't say):

        leal    4(%esp), %ecx
        andl    $-16, %esp
        pushl   -4(%ecx)
Save frame pointer using standard convention:

        pushl   %ebp
        movl    %esp, %ebp
Inscrutable madness:

        pushl   %ecx
        popl    %ecx
Restore the frame pointer and the stack pointer:

        popl    %ebp
        leal    -4(%ecx), %esp
Return:

        ret
More info for the debugger?:

        .size   main, .-main
        .ident  "GCC: (Debian 4.3.2-1.1) 4.3.2"
        .section        .note.GNU-stack,"",@progbits
By the way, main is special and magical; when I compile

int f(void) {
  return 17;
}
I get something slightly more sane:

        .file   "f.c"
        .text
        .p2align 4,,15
.globl f
        .type   f, @function
f:
        pushl   %ebp
        movl    $17, %eax
        movl    %esp, %ebp
        popl    %ebp
        ret
        .size   f, .-f
        .ident  "GCC: (Debian 4.3.2-1.1) 4.3.2"
        .section        .note.GNU-stack,"",@progbits
There's still a ton of decoration, and we're still saving the frame pointer, moving it, and restoring it, which is utterly pointless, but the rest of the code make sense.