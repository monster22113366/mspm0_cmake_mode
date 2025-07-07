#ifndef HARDWARE_H
#define HARDWARE_H

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/driverlib/driverlib.h>


#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

/*****************************Define for system****************************************************/
#define POWER_STARTUP_DELAY                                                (16)


#define CPUCLK_FREQ                                                     32000000
/**************************************************************************************************/


/*****************************Defines for TIMER_0*********************************************/
#define TIMER_0_INST                                                     (TIMG0)
#define TIMER_0_INST_IRQHandler                                 TIMG0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMG0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                           (999U)
/***************************************************************************************/

/*****************************Defines for UART_0******************************************/
#define UART_0_INST                                                        UART0
#define UART_0_INST_FREQUENCY                                            4000000
// #define UART0_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                  (9600)
#define UART_0_IBRD_4_MHZ_9600_BAUD                                         (26)
#define UART_0_FBRD_4_MHZ_9600_BAUD                                          (3)
/**********************************************************************************************/


/**************************** Port definition for Pin Group GPIO_GRP_0****************************/
#define GPIO_GRP_0_PORT                                                  (GPIOA)
/************************************************************************************************/


/**********Defines for PIN_0: GPIOA.14 with pinCMx 36 on package pin 7*****************************/
#define GPIO_GRP_0_PIN_0_PIN                                    (DL_GPIO_PIN_14)
#define GPIO_GRP_0_PIN_0_IOMUX                                   (IOMUX_PINCM36)
/*********************************************************************************************************/


/* clang-format on */

/*************************function declaration************************************************************************/
void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_TIMER_0_init(void);
SYSCONFIG_WEAK void SYSCFG_DL_UART_0_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

/****************************************************************************************************/
#ifdef __cplusplus
}
#endif



#endif


