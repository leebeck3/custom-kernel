#include "common.h"

#pragma once

extern struct process *proc_a;
extern struct process *proc_b;
extern char __free_ram[], __free_ram_end[];

struct sbiret {
	long error;
	long value;
};

struct trap_frame {
	uint32_t ra;
	uint32_t gp;
	uint32_t tp;
	uint32_t t0;
	uint32_t t1;
	uint32_t t2;
	uint32_t t3;
	uint32_t t4;
	uint32_t t5;
	uint32_t t6;
	uint32_t a0;
	uint32_t a1;
	uint32_t a2;
	uint32_t a3;
	uint32_t a4;
	uint32_t a5;
	uint32_t a6;
	uint32_t a7;
	uint32_t s1;
	uint32_t s2;
	uint32_t s3;
	uint32_t s4;
	uint32_t s5;
	uint32_t s6;
	uint32_t s7;
	uint32_t s8;
	uint32_t s9;
	uint32_t s10;
	uint32_t s11;
	uint32_t sp;
} __attribute__((packed));

void putchar(char ch);
void yield(void);
paddr_t alloc_pages(uint32_t n);
void map_page(uint32_t *table1, uint32_t vaddr, paddr_t paddr, uint32_t flags);

#define PANIC(fmt, ...)									\
	do {										\
		printf("PANIC: %s:%d: " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__);   \
		while (1) {}								\
	} while (0)

#define READ_CSR(reg)							\
	({								\
	 	unsigned long __tmp;					\
		__asm__ __volatile__("csrr %0, " #reg : "=r"(__tmp));	\
		__tmp;							\
	})								

#define WRITE_CSR(reg, value)						\
	do {								\
		uint32_t __tmp = (value);				\
		__asm__ __volatile__("csrw " #reg ", %0" ::"r"(__tmp));	\
	} while (0)

#define SATP_SV32 (1u << 31)
#define PAGE_V    (1 << 0)
#define PAGE_R    (1 << 1)
#define PAGE_W    (1 << 2)
#define PAGE_X    (1 << 3)
#define PAGE_U    (1 << 4)
