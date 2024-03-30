section .data
a dq 0
vectorsize dq 0
section .text
bits 64
default rel


global scalarMultiply
global vectorAddition


scalarMultiply:
	; 1st parameter (vector size) is stored in RCX as our loop counter
	; 2nd parameter (pointer to vector/array) is stored in RDX
	; 3rd parameter (pointer to Z: the array that contains the results) is stored in R8
	movsd [a], xmm3 ; 4th parameter (A) is stored in xmm2 and will be stored in a variable
	mov r15, 0 ; r15 will act as our array indexer

	MULLOOP:
		movsd xmm0, [rdx + r15] ; access the current value of the array
		MULSD xmm0, [a] ; multiply the value in the array by A
		movsd [r8 + r15], xmm0 ; store the new value in Z
		add r15, 8 ; increment the counter by 8 bytes (64-bits away)
		LOOP MULLOOP

	MULFINIS: NOP

	ret

vectorAddition:

	; 1st parameter (vector size) is stored in RCX as our loop counter
	mov r15, 0 ; r15 will act as our array indexer

	ADDLOOP:
		movsd xmm1, [rdx + r15] ; point to current value of 1st vector
		movsd xmm2, [r8 + r15] ; point to current value of 2nd vector
		addsd xmm1, xmm2 ; add both elements
		movsd xmm0, xmm1 ; move the result into the return value

		; store the result in 1st vector
		movsd [rdx + r15], xmm0

		add r15, 8 ; increment the index by 8 bytes (64 bits away)
		LOOP ADDLOOP

	ADDFINIS: NOP

	ret
