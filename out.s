.global _start
.section .text
_start:
    mov $60, %rax
    mov $11, %rdi
    syscall
