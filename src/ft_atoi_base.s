bits 64
extern ft_strlen

section .text
global  ft_atoi_base

ft_atoi_base:
	;----------------------------------------------------------------------
	; 1. Function Prologue
	; ---------------------------------------------------------------------
	; rdi = number string
	; rsi = base string
	; Return value in rax
	; ---------------------------------------------------------------------

	;    Save rbx (callee-saved) System V ABI Calling Convention
	push rbx

	;   Prepare call for ft_strlen
	mov rbx, rdi; rbx is actually the number string (just a temp storage)

	mov  rdi, rsi
	call ft_strlen
	mov  r8, rax; r8 = base length

	sub rsp, 256*4
	mov rdi, rsp; rbx points to the start of the array (256 integers)

	mov ecx, 256
	mov eax, -1
	rep stosd; store eax at [rdi], and increment rdi by 4 (size of dword)
	mov rdi, rbx; rdi = string to convert
	mov rbx, rsp; rbx = start of table

	xor rdx, rdx

.fill_loop:
	movzx rax, byte [rsi + rdx]
	test  al, al
	jz    .fill_done
	mov   dword [rbx + rax*4], edx; rax contains the base character ASCII value (because of mov al, byte ...)
	inc   rdx
	jmp   .fill_loop

.fill_done:
	xor r9, r9

.loop:
	movzx rax, byte [rdi]
	test  al, al
	jz    .done
	mov   edx, [rbx + rax*4]
	cmp   edx, -1
	je    .done
	imul  r9d, r8d
	add   r9d, edx
	inc   rdi
	jmp   .loop

.done:
	mov eax, r9d
	add rsp, 256*4
	pop rbx
	ret

