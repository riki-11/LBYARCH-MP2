section .data
vectorsize dq 0
section .text
bits 64
default rel

global doublesum
global scalarMultiply
global getVectorSize

doublesum:
	addsd xmm0, xmm2
	addsd xmm0, xmm1 ; xmm0 in 1st param, xmm1 in 2nd param, answer in xmm0
	
	ret

scalarMultiply:
	movsd [vectorsize], xmm0 ; Move A to a variable
	movsd xmm0, [rcx] ; access the first value of the vector
	MULSD xmm0, [vectorsize] ; multiply the first value of the vector by A
	ret

getVectorSize:
	mov rax, rcx
	ret