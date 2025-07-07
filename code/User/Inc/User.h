#ifndef USER_H
#define USER_H

/*********************************头文件引入**********************************************/
/*引入c标准库*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>


/*引入ti标准库*/
#include <ti/devices/msp/msp.h>  // 设备特定头文件 - 必须在driverlib之前
#include "driverlib.h"



/*引入User层头文件*/
#include "main.h"
#include "hardware_init.h"
#include "mspm0g3507_it.h"

/*引入App层头文件*/
#include "scheduler.h"
#include "appuart.h"
/*******************************************************************************************/









#endif


