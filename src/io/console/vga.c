#pragma once

// To display text, we write to this location.
volatile uint16_t *vga_buffer = (uint16_t *)0xb8000;
// VGA textmode buffer size.
const int VGA_COLS = 80;
const int VGA_ROWS = 25;
const int VGA_SIZE = VGA_COLS * VGA_ROWS;

enum vga_color_enum {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

uint16_t vga_entry(char c, uint8_t color) {
  return ((uint16_t)color << 8) | c;
}

uint8_t vga_color(enum vga_color_enum bg, enum vga_color_enum fg) {
  return ((uint8_t)bg << 4) | fg;
}
