#!/bin/bash
# A simple script for macOS to build and run ghOSt.
# Requires i386-elf-gcc, can be installed with `brew install i386-elf-gcc`

# Install prerequisites.
# brew install i386-elf-gcc
# brew install i386-elf-binutils
# brew install i386-elf-gdb

# Build it.
echo "Started building"
i386-elf-gcc -std=gnu99 -ffreestanding -g -c boot.s -o boot.o
i386-elf-gcc -std=gnu99 -ffreestanding -g -c kernel.c -o kernel.o
i386-elf-gcc -ffreestanding -nostdlib -g -T linker.ld boot.o kernel.o -o ghost.elf -lgcc
echo "Finished building"

# Run it.
echo "Started running"
qemu-system-i386 -kernel ghost.elf
echo "Stopped running"
