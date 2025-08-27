global ft_strcmp

section .text
ft_strcmp:
xor rax, rax
.loop:
  mov al, [rdi]
  mov bl, [rsi]
  cmp al, bl
  jne .end

  test al, bl
  je .end

  inc rdi
  inc rsi
  jmp .loop

.end:
  sub al, bl
  movzx rax, al
  ret

