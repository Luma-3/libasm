global ft_strcpy

section .text
ft_strcpy:
  mov rax, rdi
  
  .loop:
  lodsb
  stosb
  test al, al
  jnz .loop
  ret


