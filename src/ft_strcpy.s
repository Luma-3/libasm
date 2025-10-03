global ft_strcpy

section .text
ft_strcpy:
	mov rcx, rdi

.loop:
	lodsb
	stosb
	test al, al
	jnz .loop
	mov rax, rcx
	ret


