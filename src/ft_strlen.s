bits 64

global ft_strlen

section .text

ft_strlen:
	cld   ; clear direction flag ! if before code modified it
	mov   rcx, -1; set rcx to -1 (0xffffffffffffffff) for repnz scasb (infinite count)
	xor   al, al; set al to 0 (null terminator)
	repnz scasb; scan for null terminator, rcx will be decremented
	not   rcx; take negation of rcx for invert number of decrement
	lea   rax, qword [rcx - 1]; rax = rcx - 1 = length of string
	ret

