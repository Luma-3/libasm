global ft_strlen

section .text
  ft_strlen:
    mov rcx, -1 ; set rcx to -1 (0xffffffffffffffff) for repnz scasb (infinite count)
    xor al, al ; set al to 0 (null terminator)
    repnz scasb ; scan for null terminator, rcx will be decremented
    not rcx ; take negation of rcx for invert number of decrement
    lea rax, [rcx - 1] ; rax = rcx - 1 = length of string
    ret

  ;   mov rbx, rdi
  ;
  ; .loop:
  ;   mov al, byte [rbx]
  ;   test al, al
  ;   jz .end
  ;   inc rbx
  ;   jmp .loop
  ;
  ; .end:
  ;   sub rbx, rdi
  ;   mov rax, rbx
  ;   ret

