bits 64

global ft_strlen
	
section .text
	ft_strlen:
		xor rax, rax	;
		mov rcx, -1		;
		repne scasb		;
		not rcx			;
		dec rcx			;
		mov rax, rcx	;
		ret				;

