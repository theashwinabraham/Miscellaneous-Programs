; AUTHOR: ASHWIN ABRAHAM

; This code defines two functions that, calculate the factorial of an integer (given as input), one iteratively and the other recursively
; These functions can then be called from a C/C++ source file, after linking the file to the object module produced by assembling this file

section .text
    global fact_rec
    global fact_loop

    fact_loop:
        push rbp
        mov rbp, rsp

        mov eax, 1
        cmp edi, 0
        jle ret_fact_loop

        push rcx
        mov ecx, edi
        loop_fact_loop:
            imul eax, ecx
        loop loop_fact_loop
        pop rcx

        ret_fact_loop:
            pop rbp
            ret


    fact_rec:
        push rbp
        mov rbp, rsp

        mov eax, 1
        cmp edi, 0
        jle ret_fact_rec

        dec edi
        call fact_rec
        inc edi
        imul eax, edi

        ret_fact_rec:
            pop rbp
            ret