section .data
codes: db '0123456789ABCDEFC'

section .text
global _start
_start:
  mov rax, 0x1122334455667788
  mov rdi, 1
  mov rdx, 1
  mov rcx, 64

.loop:
  push rax
  sub rcx, 4 ;64 - 4 rcx
  sar rax, cl ; 60 / 4 = 15 shift -> 0x8877665544332211
  and rax, 0xf ; 0x1

  lea rsi, [codes + rax] ; codes refer lead addr and rax is shifted from lead adder -> rsi ->'s1'
  mov rax, 1 ; system call 1
  push rcx
  syscall
  pop rcx

  pop rax
  test rcx, rcx
  jnz .loop

  mov rax, 60
  xor rdi, rdi
  syscall
