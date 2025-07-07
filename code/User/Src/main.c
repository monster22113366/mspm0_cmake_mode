#include "User.h"




int main(void)
{
    SYSCFG_DL_init();

    //初始化任务调度器
    tasknum_init();

    while (1)
    {
        task_run();
    }
}





