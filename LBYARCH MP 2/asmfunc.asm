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
	mov R12, rcx ; r12 will contain the pointer to our array
	movsd xmm0, [r12] ; access the first value of the vector
	mov rcx, r8 ; save the vector size into rcx as this will be our loop counter
	MOV R15, 0 ; this acts as our index into the array.



	L1:
		movsd xmm0, [r12 + r15] ; access the current value of the array
		MULSD xmm0, [vectorsize] ; multiply the first value of the vector by A
		movsd [r12 + r15], xmm0 ; update the array accordingly.
		add r15, 8 ; increment the counter by 8 bytes (64-bits away)
		LOOP L1

	FINIS: NOP

	ret

getVectorSize:
	mov rax, rcx
	ret