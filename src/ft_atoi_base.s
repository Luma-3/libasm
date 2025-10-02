global ft_atoi_base

extern ft_strlen

section .text
ft_atoi_base:
  push rbx
  sub rsp, 8 ; align rsp % 16
  sub rsp, 256*4
  mov rbx, rsp
  
  mov rcx, rdi
  mov rdi, rsi
  call ft_strlen
  mov r8, rax
  mov rsi, rdi
  mov rdi, rcx

  xor rcx, rcx
.init_loop:
  cmp ecx, 256
  je .init_done
  mov dword [rbx+rcx*4], -1 ;dword = double-word
  inc rcx
  jmp .init_loop
  
.init_done:

  xor rdx, rdx
.fill_loop:
  movzx rax, byte [rsi + rdx]
  test al, al
  jz .fill_done
  mov [rbx + rax*4], edx ; rax contains the base character ASCII value (because of mov al, byte ...)
  inc rdx
  jmp .fill_loop

.fill_done:
  xor r9, r9

.loop:
  movzx rax, byte [rdi]
  test al, al
  jz .done
  mov edx, [rbx + rax*4]
  cmp edx, -1
  je .done
  imul r9d, r8d
  add r9d, edx
  inc rdi 
  jmp .loop

.done:

  mov eax, r9d
  add rsp, 256*4
  add rsp, 8
  pop rbx
  ret

