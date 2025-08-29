global ft_read

extern __errno_location

section .text
ft_read:
  mov rax, 0
  syscall

  test rax, rax
  jge .success

  mov rcx, rax ; save syscall return error
  call __errno_location wrt ..plt ; get errno locaiton in rax
  neg rcx
  mov [rax], ecx

  mov rax, -1 ; return value -1

.success:
  ret

