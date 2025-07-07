#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <stdint.h>
/*声明全局变量*/
extern volatile uint32_t uwTick;

/*声明函数*/
void tasknum_init(void);
void task_run(void);


#endif


