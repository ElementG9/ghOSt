#pragma once

// To display text, we write to this location.
volatile uint16_t *vga_buffer = (uint16_t *)0xb8000;
// VGA textmode buffer size.
const int VGA_COLS = 80;
const int VGA_ROWS = 25;
const int VGA_SIZE = VGA_COLS * VGA_ROWS;

enum vga_color_enum {
  VGA_COLOR_BLACK         = 0x0,
  VGA_COLOR_BLUE          = 0x1,
  VGA_COLOR_GREEN         = 0x2,
  VGA_COLOR_CYAN          = 0x3,
  VGA_COLOR_RED           = 0x4,
  VGA_COLOR_MAGENTA       = 0x5,
  VGA_COLOR_BROWN         = 0x6,
  VGA_COLOR_LIGHT_GREY    = 0x7,
  VGA_COLOR_DARK_GREY     = 0x8,
  VGA_COLOR_LIGHT_BLUE    = 0x9,
  VGA_COLOR_LIGHT_GREEN   = 0xa,
  VGA_COLOR_LIGHT_CYAN    = 0xb,
  VGA_COLOR_LIGHT_RED     = 0xc,
  VGA_COLOR_LIGHT_MAGENTA = 0xd,
  VGA_COLOR_LIGHT_BROWN   = 0xe,
  VGA_COLOR_WHITE         = 0xf,
};

uint16_t vga_entry(char c, uint8_t color) {
  return ((uint16_t)color << 8) | c;
}

uint8_t vga_color(enum vga_color_enum bg, enum vga_color_enum fg) {
  return ((uint8_t)bg << 4) | fg;
}
