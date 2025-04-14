#!/bin/bash
set -xue

# QEMU file path
QEMU=qemu-system-riscv32
OBJCOPY=/usr/bin/llvm-objcopy
CC=clang
CFLAGS="-std=c11 -O2 -g3 -Wall -Wextra --target=riscv32-unknown-elf -fno-stack-protector -ffreestanding -nostdlib"

$CC $CFLAGS -Wl, -Tuser.ld -Wl,-Map=shell.map -o shell.elf shell.c user.c common.c
$OBJCOPY --set-section-flags .bss=alloc,contents -O binary shell.elf shell.bin
$OBJCOPY -Ibinary -O elf32-littleriscv shell.bin shell.bin.o

$CC $CFLAGS -Wl, -Tkernel.ld -Wl,-Map=kernel.map -o kernel.elf \
	kernel.c common.c process.c shell.bin.o

#Start QEMU
$QEMU -machine virt -bios default -nographic -serial mon:stdio --no-reboot \
	-kernel kernel.elf
