
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            global.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#define GLOBAL_VARIABLES_HERE

#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "proc.h"
#include "global.h"


PUBLIC	PROCESS			proc_table[NR_TASKS];

PUBLIC 	SEMAPHORE 		semaphore;

PUBLIC	char			task_stack[STACK_SIZE_TOTAL];

PUBLIC	TASK	task_table[NR_TASKS] = {
                    {TestA, STACK_SIZE_TESTA, "TestA"},
					{TestB, STACK_SIZE_TESTB, "TestB"},
					{TestC, STACK_SIZE_TESTC, "TestC"},
					{TestD, STACK_SIZE_TESTD, "TestD"},
					{TestE, STACK_SIZE_TESTE, "TestE"}
                };

PUBLIC	irq_handler		irq_table[NR_IRQ];      //中断数组

PUBLIC	system_call		sys_call_table[NR_SYS_CALL] = {sys_get_ticks,
								sys_disp_str,
								sys_disp_color_str,
								sys_process_sleep,
								sys_sem_p,
								sys_sem_v,
								sys_process_wakeup};

