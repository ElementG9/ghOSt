#include "sources.c"

// Check we're using the correct compiler.
#if defined(__linux__)
  #error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
  #error "This code must be compiled with an x86-elf compiler"
#endif

void kernel_main() {
  gdt_install();
  term_init();

  term_print("Welcome to ghOSt v0.1.0\n");
  term_print("Hello world!\n");

  char intbuf[20];
  for (int i = 0; i < 22; i++) {
    itoa(i, intbuf, 10);
    term_print(intbuf);
    term_print("\n");
  }
}
