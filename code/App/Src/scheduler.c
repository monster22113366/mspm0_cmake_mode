#include "User.h"
#include <stdint.h>

volatile uint32_t uwTick;
uint8_t task_num = 0;
uint32_t fuck;
typedef struct 
{
    void (*func) (void);
    uint16_t task_period;
    uint32_t task_lastrun;
}task_t;

void test(void)
{
    fuck++;
}
task_t task_list[] = 
{
    {uart_task,200,0},
};

void tasknum_init(void)
{
    task_num = sizeof(task_list)/sizeof(task_t);
}



void task_run(void)
{
    for(uint8_t i = 0; i < task_num; i++)
    {
        uint32_t now_time = uwTick;
        if((now_time - task_list[i].task_lastrun) >= task_list[i].task_period)
        {
            task_list[i].task_lastrun = now_time;
            task_list[i].func();
        }
    }
}