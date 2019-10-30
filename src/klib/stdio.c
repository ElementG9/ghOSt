#pragma once
#include <stddef.h>
#include <stdint.h>
#include "./stdlib.c"

char *itoa(int value, char *buffer, int base) {
  // Taken from https://www.techiedelight.com/implement-itoa-function-in-c/
  // Invalid input.
  if (base < 2 || base > 32)
    return buffer;

  // Consider absolute value of number.
  int n = abs(value);

  int i = 0;
  while (n) {
    int r = n % base;

    if (r >= 10)
      buffer[i++] = 65 + (r - 10);
    else
      buffer[i++] = 48 + r;

    n = n / base;
  }

  // If number is 0
  if (i == 0)
    buffer[i++] = '0';

  // If base is 10 and value is negative, the resulting string
  // is preceded with a minus sign (-).
  // With any other base, value is always considered unsigned.
  if (value < 0 && base == 10)
    buffer[i++] = '-';

  buffer[i] = '\0'; // Null terminate string.

  // Reverse the string and return it.
  int a = 0;
  int b = i - 1;
  while (a < b) {
    char t = buffer[a];
    buffer[a] = buffer[b];
    buffer[b] = t;
    a++;
    b--;
  }

  return buffer;
}
