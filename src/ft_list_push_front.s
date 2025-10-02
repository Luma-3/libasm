bits 64

section .text
global ft_list_push_front

; void ft_list_push_front(t_list **begin_list, t_list *node);
; Parameters:
; 1. begin_list (rdi) - pointer to the head of the list
; 2. node (rsi) - new node to add at the front
; Return value: None


ft_list_push_front:
  mov rax, [rdi]
  mov [rdi + 8], rax
  mov [rdi], rsi
  ret
