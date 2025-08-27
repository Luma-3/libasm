global ft_strcpy

section .text
ft_strcpy:
  mov rax, rdi
  
  .loop:
  mov al, [rsi]
  mov [rdi], al
  inc rdi
  inc rsi
  test al, al
  jnz .loop
  ret


