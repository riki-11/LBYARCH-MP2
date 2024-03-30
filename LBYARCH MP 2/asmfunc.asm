section .data

section .text
bits 64
default rel

global doublesum
global scalarMultiply

doublesum:
	addsd xmm0, xmm2
	addsd xmm0, xmm1 ; xmm0 in 1st param, xmm1 in 2nd param, answer in xmm0
	
	ret

scalarMultiply:
	movss xmm10, xmm0 ; move the value of to another register
	movsd xmm0, [rcx+16] ; access the first value of the vector
	ret