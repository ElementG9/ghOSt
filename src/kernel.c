#include "sources.c"

// Check we're using the correct compiler.
#if defined(__linux__)
  #error "This code must be compiled with a cross-compiler"
#elif !defined(__i386__)
  #error "This code must be compiled with an x86-elf compiler"
#endif

void kernel_main() {
  term_init();
  term_print("Welcome to ghOSt v0.1.0\n");
  term_print("Hello world!\n");
}
