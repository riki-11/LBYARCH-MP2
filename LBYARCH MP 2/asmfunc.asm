section .data
msg1 db "Hello World", 13, 10, 0

section .text
bits 64
default rel

global intsum
extern printf

intsum: 
	push rsi ; save non-volatile if needed
	push rdi ;
	push rbp ; setup frame
	mov rbp, rsp 
	mov rcx, msg1

	mov rax, rcx ;1st parameter
	add rax, rdx ; 2nd parameter
	add rax, r8 ; 3rd parameter

	pop rbp
	pop rsi
	pop rdi

	ret