; AUTHOR: ASHWIN ABRAHAM

; This program stores input from the user in a buffer of length 14, and then prints out the input
; It doesn't use any library functions, but rather relies only on the read and write Linux syscalls

section .data
buf times 14 db 0
len EQU $-buf


section .text
global _start

_start:
    xor rax, rax
    xor rdi, rdi
    mov rsi, buf
    mov rdx, len
    syscall

    mov rax, 1
    mov rdi, 1
    mov rsi, buf
    mov rdx, len
    syscall

    xor rdi, rdi
    mov rax, 60
    syscall