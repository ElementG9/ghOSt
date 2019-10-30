CC=i386-elf-gcc
AS=i386-elf-gcc
LD=i386-elf-gcc
ASFLAGS=-std=gnu99 -ffreestanding -g
CCFLAGS=-std=gnu99 -ffreestanding -g
LDFLAGS=-ffreestanding -nostdlib -g

EMU=qemu-system-i386
EMUFLAGS=-kernel

SRC=./src
ARCH_i386=$(SRC)/arch/i386
KERNEL=$(SRC)/kernel.o
#OBJ_FILES=$(shell find . -name '*.s')
OBJ_FILES=$(patsubst $(ARCH_i386)/%.s,$(ARCH_i386)/%.o,$(shell find . -name '*.s'))

all: build run

build: $(KERNEL) $(OBJ_FILES)
	$(LD) $(LDFLAGS) -T linker.ld -o ghOSt.elf -lgcc $(OBJ_FILES) $(KERNEL)

run:
	$(EMU) $(EMUFLAGS) ghOSt.elf

clean:
	@rm -r $(shell find . -name '*.o')
	@rm -r $(shell find . -name '*.elf')

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) -c $< -o $@
