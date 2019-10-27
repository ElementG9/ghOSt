CC=i386-elf-gcc
COMPILEFLAGS=-std=gnu99 -ffreestanding -g
LINKERFLAGS=-ffreestanding -nostdlib -g

QEMU=qemu-system-i386
QEMUFLAGS=-kernel

SRC=src
ARCH_i386=$(SRC)/arch/i386
KERNEL=$(SRC)/kernel.o
OBJ_FILES=$(shell find . -name '*.s')#$(patsubst $(ARCH_i386)/%.s,$(ARCH_i386)/%.o,$(shell find . -name '*.s'))

all: run

build: $(KERNEL) $(OBJ_FILES)
	$(CC) $(LINKERFLAGS) -T linker.ld -o ghOSt.elf -lgcc $(OBJ_FILES) $(KERNEL)

run: build
	$(QEMU) $(QEMUFLAGS) ghOSt.elf

clean:
	@rm -r $(shell find . -name '*.o')
	@rm -r $(shell find . -name '*.elf')

%.o: %.c
	@$(CC) $(COMPILEFLAGS) -c $< -o $@

%.o: %.s
	@$(CC) $(COMPILEFLAGS) -c $< -o $@
