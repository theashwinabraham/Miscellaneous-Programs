; AUTHOR: ASHWIN ABRAHAM

; This code calculates the nth Fibonacci number, for a given n, using 4 different algorithms

section .rodata
    format_printf_loop db 'Loop Fibonacci', 58, ' %d', 10, 0
    format_printf_rec db 'Recursive Fibonacci', 58, ' %d', 10, 0
    format_printf_TR_no db 'Unoptimized Tail Recursive Fibonacci', 58, ' %d', 10, 0
    format_printf_TR_o db 'Optimized Tail Recursive Fibonacci', 58, ' %d', 10, 0
    format_scanf db '%d', 0

section .text
global main
extern printf
extern scanf

loop_fib:
    push rbp
    mov rbp, rsp

    mov eax, 0
    cmp edi, 0
    jle ret_loop_fib

    push rbx
    mov ebx, 1
    mov ecx, edi
    head:
        mov edx, eax
        mov eax, ebx
        add ebx, edx
    loop head

    pop rbx


    ret_loop_fib:
        pop rbp
        ret

rec_fib:
    push rbp
    mov rbp, rsp

    mov eax, 0
    cmp edi, 0
    jle ret_rec_fib

    mov eax, 1
    cmp edi, 1
    je ret_rec_fib

    push rcx

    dec edi
    call rec_fib
    mov ecx, eax

    dec edi
    call rec_fib
    add eax, ecx

    pop rcx

    add edi, 2

    ret_rec_fib:
        pop rbp
        ret

TR_rec_fib:
    push rbp
    mov rbp, rsp

    mov eax, esi
    cmp edi, 0
    jle ret_TR_rec_fib

    push rsi
    push rdx

    mov ecx, edx
    add edx, esi
    mov esi, ecx

    dec edi

    call TR_rec_fib

    pop rdx
    pop rsi
    inc edi

    ret_TR_rec_fib:
        pop rbp
        ret

TR_fib:
    push rbp
    mov rbp, rsp

    top_TR_fib:
        mov eax, esi
        cmp edi, 0
        jle ret_TR_fib

        mov ecx, edx
        add edx, esi
        mov esi, ecx

        dec edi
    jmp top_TR_fib

    ret_TR_fib:
        pop rbp
        ret

main:
    push rbp
    mov rbp, rsp

    sub rsp, 16

    inf:
        mov rdi, format_scanf
        lea rsi, [rbp-4]
        call scanf WRT ..plt

        mov edi, [rbp-4]
        call loop_fib
        mov esi, eax
        mov rdi, format_printf_loop
        call printf WRT ..plt

        mov edi, [rbp-4]
        mov esi, 0
        mov edx, 1
        call TR_fib
        mov esi, eax
        mov rdi, format_printf_TR_o
        call printf WRT ..plt

        mov edi, [rbp-4]
        mov esi, 0
        mov edx, 1
        call TR_rec_fib
        mov esi, eax
        mov rdi, format_printf_TR_no
        call printf WRT ..plt

        mov edi, [rbp-4]
        call rec_fib
        mov esi, eax
        mov rdi, format_printf_rec
        call printf WRT ..plt
    jmp inf

    xor eax, eax
    mov rsp, rbp
    pop rbp
    ret