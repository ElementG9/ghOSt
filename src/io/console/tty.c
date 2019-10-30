#pragma once
#include "./vga.c"

// Display in the top-left.
int term_col = 0;
int term_row = 0;
uint8_t term_color = 0x0f; // const version of vga_color(VGA_COLOR_BLACK, VGA_COLOR_WHITE).

void term_init() {
  // Clear the textmode buffer.
  for (int col = 0; col < VGA_COLS; col++)
    for (int row = 0; row < VGA_ROWS; row++) {
      const size_t index = (VGA_COLS * row) + col;
      vga_buffer[index] = vga_entry(' ', vga_color(VGA_COLOR_BLACK, VGA_COLOR_BLACK)); // Black on black
    }
}

void term_putc(char c) {
  switch (c) {
  case '\n': {
    term_col = 0;
    term_row++;
    break;
  }

  default: {
    const size_t index = (VGA_COLS * term_row) + term_col;
    vga_buffer[index] = vga_entry(c, term_color);
    term_col++;
    break;
  }
  }
  if (term_col >= VGA_COLS) {
    term_col = 0;
    term_row++;
  }
  if (term_row >= VGA_ROWS) {
    // Move the screen up.
    for (int i = VGA_COLS; i < VGA_SIZE; i++)
      vga_buffer[i - VGA_COLS] = vga_buffer[i];
    // Clear the bottom row.
    for (int i = VGA_SIZE - VGA_COLS; i < VGA_SIZE; i++)
      vga_buffer[i] = vga_entry(' ', vga_color(VGA_COLOR_BLACK, VGA_COLOR_BLACK));
    // Move the cursor.
    term_row--;
    term_col = 0;
  }
}

void term_print(const char *str) {
  for (size_t i = 0; str[i] != '\0'; i++)
    term_putc(str[i]);
}
