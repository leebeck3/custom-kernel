#define PROCS_MAX 8       // Maximum number of processes

#define PROC_UNUSED   0   // Unused process control structure
#define PROC_RUNNABLE 1   // Runnable process
#define SSTATUS_SPIE (1 << 5)

struct process {
    int pid;             // Process ID
    int state;           // Process state: PROC_UNUSED or PROC_RUNNABLE
    vaddr_t sp;          // Stack pointer
    uint32_t *page_table; 
    uint8_t stack[8192]; // Kernel stack
};

void delay(void);
void proc_a_entry(void);
void proc_b_entry(void);
struct process *create_process(const void *image, size_t image_size);
extern struct process *current_proc;
extern struct process *idle_proc;
