global ft_write

extern __errno_location

section .text
  ft_write:
  mov rax, 1 ; define call code
  syscall

  test rax, rax
  jge .success

  mov rcx, rax
  call __errno_location wrt ..plt
  neg rcx
  mov [rax], ecx

  mov rax, -1

  .success:
    ret


