#!/bin/bash
set -xue

# QEMU file path
QEMU=qemu-system-riscv32

CC=clang
CFLAGS="-std=c11 -O2 -g3 -Wall -Wextra --target=riscv32-unknown-elf -fno-stack-protector -ffreestanding -nostdlib"

$CC $CFLAGS -Wl, -Tkernel.ld -Wl,-Map=kernel.map -o kernel.elf \
	kernel.c common.c process.c

#Start QEMU
$QEMU -machine virt -bios default -nographic -serial mon:stdio --no-reboot \
	-kernel kernel.elf
