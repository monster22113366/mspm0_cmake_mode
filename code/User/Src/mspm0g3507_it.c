#include "User.h"



//定时器TIMG0的中断服务函数 已配置为1毫秒的周期
void TIMG0_IRQHandler(void)
{
    //如果产生了定时器中断
    switch( DL_TimerG_getPendingInterrupt(TIMER_0_INST) )
    {
        case DL_TIMER_IIDX_ZERO: // 如果是0溢出中断
            uwTick++;
        break;
        
        default:
        break;
    }
}