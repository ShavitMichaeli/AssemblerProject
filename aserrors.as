;file
add:	add r15, LIST
r12:	prn #48
		lea STR, r6
		inc r6, a6
		mov r3, K, #3
		sub r1, r4    
		bne END
		fake K, #-6
		bne &END
		dec K
		jmp &LOOP
END:	stop
STR:	.string “abcd”
		.data 6, -9
		.data -100
K:		.data 31