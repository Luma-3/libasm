global ft_strlen

section .text
  ft_strlen:
    mov rbx, rdi

  .loop:
    mov al, byte [rbx]
    test al, al
    jz .end
    inc rbx
    jmp .loop

  .end:
    sub rbx, rdi
    mov rax, rbx
    ret

