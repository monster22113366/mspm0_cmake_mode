/**
 * @file    startup_mspm0g3507.c
 * @brief   MSPM0G3507启动文件
 * @version 1.0
 * @date    2024-12-19
 * @author  Bob (架构师)
 * 
 * @note    MSPM0G3507微控制器启动代码和中断向量表
 */

#include "User.h"

/* 栈顶地址 (由链接脚本定义) */
extern uint32_t _estack;

/* 启动代码函数声明 */
void Reset_Handler(void);
void Default_Handler(void);



/* 外部函数声明 */
extern int main(void);
extern void SystemInit(void);


/* 中断服务程序声明 */
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
/* SysTick_Handler在main.c中实现，不需要weak定义 */

/* 外设中断服务程序声明 */
void GROUP0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));  /* Port A edge triggered */
void GROUP1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));  /* Port B edge triggered */
void TIMG8_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void ADC0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void ADC1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CANFD0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DAC0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIMG0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIMG6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIMA0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIMA1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIMG7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIMG12_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));

/* 中断向量表 */
__attribute__((section(".isr_vector")))
const uint32_t g_pfnVectors[] = {
    /* Cortex-M0+ 系统中断 (0-15) */
    (uint32_t)&_estack,                 /* 0: 栈顶指针 */
    (uint32_t)Reset_Handler,            /* 1: 复位处理程序 */
    (uint32_t)NMI_Handler,              /* 2: NMI处理程序 */
    (uint32_t)HardFault_Handler,        /* 3: 硬件错误处理程序 */
    0,                                  /* 4: 保留 */
    0,                                  /* 5: 保留 */
    0,                                  /* 6: 保留 */
    0,                                  /* 7: 保留 */
    0,                                  /* 8: 保留 */
    0,                                  /* 9: 保留 */
    0,                                  /* 10: 保留 */
    (uint32_t)SVC_Handler,              /* 11: SVCall处理程序 */
    0,                                  /* 12: 保留 */
    0,                                  /* 13: 保留 */
    (uint32_t)PendSV_Handler,           /* 14: PendSV处理程序 */
    (uint32_t)SysTick_Handler,          /* 15: SysTick处理程序 */
    
    /* MSPM0G3507 外设中断 (16-37, 对应IRQ 0-21) - 基于官方文档修正 */
    (uint32_t)GROUP0_IRQHandler,        /* 16: IRQ0 - GROUP0 interrupt handler (Port A edge triggered) */
    (uint32_t)GROUP1_IRQHandler,        /* 17: IRQ1 - GROUP1 interrupt handler (Port B edge triggered) */
    (uint32_t)TIMG8_IRQHandler,         /* 18: IRQ2 - TIMG8 interrupt handler */
    (uint32_t)UART3_IRQHandler,         /* 19: IRQ3 - UART3 interrupt handler */
    (uint32_t)ADC0_IRQHandler,          /* 20: IRQ4 - ADC0 interrupt handler */
    (uint32_t)ADC1_IRQHandler,          /* 21: IRQ5 - ADC1 interrupt handler */
    (uint32_t)CANFD0_IRQHandler,        /* 22: IRQ6 - CANFD0 interrupt handler */
    (uint32_t)DAC0_IRQHandler,          /* 23: IRQ7 - DAC0 interrupt handler */
    (uint32_t)Default_Handler,          /* 24: IRQ8 - Reserved */
    (uint32_t)SPI0_IRQHandler,          /* 25: IRQ9 - SPI0 interrupt handler */
    (uint32_t)SPI1_IRQHandler,          /* 26: IRQ10 - SPI1 interrupt handler */
    (uint32_t)Default_Handler,          /* 27: IRQ11 - Reserved */
    (uint32_t)Default_Handler,          /* 28: IRQ12 - Reserved */
    (uint32_t)UART1_IRQHandler,         /* 29: IRQ13 - UART1 interrupt handler */
    (uint32_t)UART2_IRQHandler,         /* 30: IRQ14 - UART2 interrupt handler */
    (uint32_t)UART0_IRQHandler,   /* 31: IRQ15 - UART0 interrupt handler ← 关键修复点 */
    (uint32_t)TIMG0_IRQHandler,         /* 32: IRQ16 - TIMG0 interrupt handler */
    (uint32_t)TIMG6_IRQHandler,         /* 33: IRQ17 - TIMG6 interrupt handler */
    (uint32_t)TIMA0_IRQHandler,         /* 34: IRQ18 - TIMA0 interrupt handler */
    (uint32_t)TIMA1_IRQHandler,         /* 35: IRQ19 - TIMA1 interrupt handler */
    (uint32_t)TIMG7_IRQHandler,         /* 36: IRQ20 - TIMG7 interrupt handler */
    (uint32_t)TIMG12_IRQHandler,        /* 37: IRQ21 - TIMG12 interrupt handler */
};

/**
 * @brief   复位处理程序
 */
void Reset_Handler(void)
{
    /* 复制初始化数据段 */
    extern uint32_t _sidata, _sdata, _edata;
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;

    while (dst < &_edata) {
        *dst++ = *src++;
    }

    /* 清零BSS段 */
    extern uint32_t _sbss, _ebss;
    dst = &_sbss;
    while (dst < &_ebss) {
        *dst++ = 0;
    }

    /* 系统初始化 */
    SystemInit();

    /* 调用main函数 */
    main();

    /* 无限循环 */
    while (1);
}

/**
 * @brief   默认中断处理程序
 */
void Default_Handler(void)
{
    /* 无限循环 */
    while (1);
}

/**
 * @brief   系统初始化函数
 */
void SystemInit(void)
{
    /* 基本系统初始化 */
    /* 这里可以添加早期的系统初始化代码 */
    /* 如时钟配置、FPU使能等 */
}