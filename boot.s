.extern kernel_main
.global start

.set MB_MAGIC, 0x1badb002
.set MB_FLAGS, (1 << 0) | (1 << 1)
.set MB_CHECKSUM, (0 - (MB_MAGIC + MB_FLAGS))

.section .multiboot
  .align 4
  .long MB_MAGIC
  .long MB_FLAGS
  .long MB_CHECKSUM

.section .bss
  .align 16
  stack_bottom:
    .skip 4096 // The stack is 4096 bytes.
  stack_top:

.section .text
  start:
    mov $stack_top, %esp
    call kernel_main
    hang: // Hang the CPU if the kernel ever returns.
      cli
      hlt
      jmp hang
