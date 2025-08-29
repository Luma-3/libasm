global ft_strdup

extern malloc

section .text
ft_strdup:
  push rdi


.strlen:
  mov rcx, -1
  xor al, al
  repnz scasb
  not rcx
  lea rax, [rcx - 1]



.allocate:
  inc rax
  mov rdi, rax
  call malloc wrt ..plt
  test rax, rax
  jz .error

  mov rdi, rax
  mov rdx, rax
  pop rsi


.strcpy:
  lodsb
  stosb
  test al, al
  jnz .strcpy

.finish:
  mov rax, rdx
  ret

.error:
  xor rax, rax
  ret
