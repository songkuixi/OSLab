
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                               clock.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "string.h"
#include "proc.h"
#include "global.h"

extern void schedule();
extern void enable_irq(int);

/*======================================================================*
                           clock_handler
 *======================================================================*/
PUBLIC void clock_handler(int irq){
    /**
     *  Modified Here
     */
    
    //总 ticks + 1
	ticks++;
    //避免中断重入（楼下的函数会导致）
	if (k_reenter != 0) {
		return;
	}
    //ticks大于0，意味着还在睡眠
	if (p_proc_ready->ticks > 0) {
		return;
	}
    //调度进程
	schedule();
}

/*======================================================================*
                              milli_delay
 *======================================================================*/
PUBLIC void milli_delay(int milli_sec){                     //运行在用户态
    int t = get_ticks();                                    //得到 ticks
    while(((get_ticks() - t) * 1000 / HZ) < milli_sec) {}   //在 milli_Sec * 100 / HZ 个 ticks 内不退出
}

/*======================================================================*
                            init_clock
 *======================================================================*/
PUBLIC void init_clock(){
    /* 初始化 8253 PIT */
    out_byte(TIMER_MODE, RATE_GENERATOR);
    out_byte(TIMER0, (u8) (TIMER_FREQ/HZ) );
    out_byte(TIMER0, (u8) ((TIMER_FREQ/HZ) >> 8));
    
    put_irq_handler(CLOCK_IRQ, clock_handler);    /* 设定时钟中断处理程序 */
    enable_irq(CLOCK_IRQ);                        /* 让8259A可以接收时钟中断 */
}
