/*
 * stm32f407xx.h
 *
 *  Created on: Jul 26, 2026
 *      Author: Acer
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_


#include<stdint.h>

#define __vo volatile

/* Based Addresses of FLASH and SRM Memories
 *
 */

#define FLASH_BASEADDR     	       0x08000000U     /*Explain this macros briefly here's*/
#define SRAM1_BASEADDR             0x20000000U     /*Explain this macros briefly here's*/
#define SRAM2_BASEADDR             0x20001C00U     /*Explain this macros briefly here's*/
#define ROM                        0x1FFF0000U
#define RAM                        SRAM1_BASEADDR


/*  APBX & AHBX PERIPHERAL BUS ADDRESSES   */

#define PERIPH_BASE                0X00000000U
#define APB1PERIPH_BASEADDR        PERIPH_BASE
#define APB2PERIPH_BASEADDR        0X40001000U
#define AHB1PERIPH_BASEADDR        0X40020000U
#define AHB2PERIPH_BASEADDR        0X50000000U


/* Base Address of peripherals which on hanging on AHB1 bus
 *
 * to do complete all the others peripherals
 *
 */
#define GPIOA_BASEADDR                    (AHB1PERIPH_BASEADDR + 0X0000)
#define GPIOB_BASEADDR            	      (AHB1PERIPH_BASEADDR + 0X0400)
#define GPIOC_BASEADDR                    (AHB1PERIPH_BASEADDR + 0X0800)
#define GPIOD_BASEADDR                    (AHB1PERIPH_BASEADDR + 0X0C00)
#define GPIOE_BASEADDR                    (AHB1PERIPH_BASEADDR + 0X1000)
#define GPIOF_BASEADDR                    (AHB1PERIPH_BASEADDR + 0X1400)
#define GPIOG_BASEADDR                    (AHB1PERIPH_BASEADDR + 0X1800)
#define GPIOH_BASEADDR                    (AHB1PERIPH_BASEADDR + 0X1C00)
#define GPIOI_BASEADDR                    (AHB1PERIPH_BASEADDR + 0X2000)
#define RCC_BASEADDR                      (AHB1PERIPH_BASEADDR + 0X3800)

/* Base Address of peripherals which on hanging on APB1 bus
 *
 * to do complete all the others peripherals

*/
#define I2C1_BASEADDR                      (APB1PERIPH_BASEADDR + 0X5400)
#define I2C2_BASEADDR                      (APB1PERIPH_BASEADDR + 0X5800)
#define I2C3_BASEADDR                      (APB1PERIPH_BASEADDR + 0X5C00)

#define SPI2_BASEADDR                      (APB1PERIPH_BASEADDR + 0X3800)
#define SPI3_BASEADDR                      (APB1PERIPH_BASEADDR + 0X3C00)


#define USART2_BASEADDR                    (APB1PERIPH_BASEADDR + 0X4400)
#define USART3_BASEADDR                    (APB1PERIPH_BASEADDR + 0X4800)
#define USART4_BASEADDR                    (APB1PERIPH_BASEADDR + 0X4C00)
#define USART5_BASEADDR                    (APB1PERIPH_BASEADDR + 0X5000)




/* Base Addresses of peripherals which on hanging on APB2 Buses
 *  to do complete all the others peripherals
 */
#define EXIT1_BASEADDR                     (AHB2PERIPH_BASEADDR + 0X3C00)
#define SPI1_BASEADDR                      (AHB2PERIPH_BASEADDR + 0X3000)
#define SYCFG_BASEADDR                     (AHB2PERIPH_BASEADDR + 0X3800)
#define USART1_BASEADDR                    (AHB2PERIPH_BASEADDR + 0X1000)
#define USART6_BASEADDR                    (AHB2PERIPH_BASEADDR + 0X1400)


/********************** Peripherals register  Difination Register*******************/

/*  Note:  Register of Peripherals are specific to MCU
 *  example. number of register of SPI peripherals of Stm32f4xx family on MCU  may be Different (more or less)
 *  compare to number of register of SPI peripherals of stm32lxx and stm32f4xx family of MCUs
 *  Please check your device RM
 *
 */


typedef struct
{
	__vo uint32_t MODER;               /*! < GPIO port mode Register,   Address offset:0x00*/
	__vo uint32_t OTYPER;              /*! < ToDo,                      Address offset:0xo4*/
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRRL;
	__vo uint32_t BSRRH;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];            /*! AFR[1] < GPIO Alternate function low register ,    AFR[2] < GPIO Alternate function low register                   Address offset:0x20 - 0x24 */


}GPIO_RegDef_t;



typedef struct
{

	__vo uint32_t CR;                                /*TODO,           Addresses Offset: 0x00*/
	__vo uint32_t PLLCFGR;							 /*TODO,           Addresses Offset: 0x04*/
	__vo uint32_t CFGR;								 /*TODO,           Addresses Offset: 0x08*/
	__vo uint32_t CIR;								 /*TODO,           Addresses Offset: 0x0C*/
	__vo uint32_t AHB1RSTR;                          /*TODO,           Addresses Offset: 0x10*/
	__vo uint32_t AHB2RSTR;                          /*TODO,           Addresses Offset: 0x14*/
	__vo uint32_t AHB3RSTR;							 /*TODO,           Addresses Offset: 0x18*/
	 uint32_t     RESERVED0;                         /*RESERVED 0X1C */
	__vo uint32_t APB1RSTR;                          /*TODO,           Addresses Offset: 0x20*/
	__vo uint32_t APB2RSTR;							 /*TODO,           Addresses Offset: 0x24*/
	__vo uint32_t RESERVED1[2];                      /*RESERVED 0X28 - 0X2C */
	__vo uint32_t AHB1ENR;							 /*TODO,           Addresses Offset: 0x30*/
	__vo uint32_t AHB2ENR;                           /*TODO,           Addresses Offset: 0x34*/
	__vo uint32_t AHB3ENR;                           /*TODO,           Addresses Offset: 0x38*/
	 uint32_t     RESERVED2;                     /*RESERVED 0X3C */
	__vo uint32_t APB1ENR;                           /*TODO,           Addresses Offset: 0x40*/
	__vo uint32_t APB2ENR;                           /*TODO,           Addresses Offset: 0x44*/
	 uint32_t     RESERVED3[2];                      /*RESERVED 0X48-0X4C*/
	__vo uint32_t AHB1LPENR;                         /*TODO,           Addresses Offset: 0x50*/
	__vo uint32_t AHB2LPENR;                         /*TODO,           Addresses Offset: 0x54*/
	__vo uint32_t AHB3LPENR;                         /*TODO,           Addresses Offset: 0x58*/
	 uint32_t     RESERVED4;                         /*RESERVED  0X5C*/
	__vo uint32_t APB1LPENR;                         /*TODO,           Addresses Offset: 0x60*/
	__vo uint32_t APB2LPENR;                         /*TODO,           Addresses Offset: 0x64*/
	 uint32_t     RESERVED5[2];                      /*RESERVED  0X68-0X6C*/
	__vo uint32_t BDCR;                              /*TODO,           Addresses Offset: 0x70*/
	__vo uint32_t CSR;                               /*TODO,           Addresses Offset: 0x74*/
	 uint32_t     RESERVED6[2];                      /*RESERVED  0X78-0X7C*/
	__vo uint32_t SSCGR;                             /*TODO,           Addresses Offset: 0x80*/
	__vo uint32_t PLLI2SCFGR;                        /*TODO,           Addresses Offset: 0x84*/
	__vo uint32_t PLLSAICFGR;                        /*TODO,           Addresses Offset: 0x88*/
	__vo uint32_t DCKCFGR;                           /*TODO,           Addresses Offset: 0x8C*/
	__vo uint32_t CKGATENR;                          /*TODO,           Addresses Offset: 0x90*/
	__vo uint32_t DCKCFGR2;                           /*TODO,           Addresses Offset: 0X94*/


}RCC_RegeDef_t;

/*
 * peripheral register defination structure for EXTI
 *
 */
typedef struct
{
	__vo uint32_t IMR;               /*! < GPIO port mode Register,   Address offset:0x00*/
	__vo uint32_t EMR;               /*! < ToDo,                      Address offset:0xo4*/
	__vo uint32_t RTSR;              /*! < ToDo,                      Address offset:0xo8*/
	__vo uint32_t FTSR;              /*! < ToDo,                      Address offset:0xoc*/
	__vo uint32_t SWIER;             /*! < ToDo,                      Address offset:0x10*/
	__vo uint32_t PR;                /*! < ToDo,                      Address offset:0x14*/
}EXTI_RegDef_t;

/* Peripheral Definitions   (Peripheral base addresses typecasted to xxx_Regdef_t)
 *
 */
#define GPIOA                           ((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB							((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC							((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD							((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE							((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF							((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG							((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH							((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI							((GPIO_RegDef_t*)GPIOI_BASEADDR)

#define RCC                             ((RCC_RegeDef_t*)RCC_BASEADDR)

#define EXTI                            ((EXTI_RegeDef_t*)EXTI_BASEADDR)




/* clock ENable Macros for GPIOs Peripherals*/
#define GPIOA_PCLK_EN()     (RCC-> AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()     (RCC-> AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()     (RCC-> AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()     (RCC-> AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()     (RCC-> AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN()     (RCC-> AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN()     (RCC-> AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN()     (RCC-> AHB1ENR |= (1 << 7))
#define GPIOI_PCLK_EN()     (RCC-> AHB1ENR |= (1 << 8))

/* clock ENable Macros for I2Cs  Peripherals*/


#define I2C1_PCLK_EN()     (RCC-> APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()     (RCC-> APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()     (RCC-> APB1ENR |= (1 << 23))

/* clock ENable Macros for SPIs  Peripherals*/
#define SPI1_PCLK_EN()     (RCC-> APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()     (RCC-> APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()     (RCC-> APB1ENR |= (1 << 15))
#define SPI4_PCLK_EN()     (RCC-> APB2ENR |= (1 << 13))

/*  clock ENable Macros for USARTs  Peripherals */
#define USART1_PCCK_EN()     (RCC-> APB2ENR |= (1 << 4))
#define USART2_PCCK_EN()     (RCC-> APB1ENR |= (1 << 17))
#define USART3_PCCK_EN()     (RCC-> APB1ENR |= (1 << 18))
#define USART4_PCCK_EN()     (RCC-> APB1ENR |= (1 << 19))
#define USART5_PCCK_EN()     (RCC-> APB1ENR |= (1 << 20))
#define USART6_PCCK_EN()     (RCC-> APB1ENR |= (1 << 5))

/* clock ENable Macros for SYSCFG  Peripherals */
#define SYSCFG_PCCK_EN()     (RCC-> APB2ENR |= (1 << 14))

/******************************************************/
 /*  clock DIable Macros for GPIOs Peripherals*/
#define GPIOA_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 7))
#define GPIOI_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 8))
/* Clock Disable macros for SPIx peripherals
 *
 */

/* Clock Disable Macros for USARTx Peripherals
 *
 *
 */

/* Clock Disable Macros for SYSCFGx Peripherals
 *
 *
 */

/* Macros  to Reset GPIOs peripherals
 *
 */
#define GPIOA_REG_RESET()               do{(RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &=  ~(1 << 0)) ;}while(0)
#define GPIOB_REG_RESET()               do{(RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &=  ~(1 << 1)) ;}while(0)
#define GPIOC_REG_RESET()               do{(RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &=  ~(1 << 2)) ;}while(0)
#define GPIOD_REG_RESET()               do{(RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &=  ~(1 << 3)) ;}while(0)
#define GPIOE_REG_RESET()               do{(RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &=  ~(1 << 4)) ;}while(0)
#define GPIOF_REG_RESET()               do{(RCC->AHB1RSTR |= (1 << 5)); (RCC->AHB1RSTR &=  ~(1 << 5)) ;}while(0)
#define GPIOG_REG_RESET()               do{(RCC->AHB1RSTR |= (1 << 6)); (RCC->AHB1RSTR &=  ~(1 << 6)) ;}while(0)
#define GPIOH_REG_RESET()               do{(RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &=  ~(1 << 7)) ;}while(0)
#define GPIOI_REG_RESET()               do{(RCC->AHB1RSTR |= (1 << 8)); (RCC->AHB1RSTR &=  ~(1 << 8)) ;}while(0)






// SOME GENERIC MACROS
#define ENABLE         1
#define DISABLE        0
#define SET            ENABLE
#define RESET          DISABLE
#define GPIO_PIN_SET    SET
#define GPIO_PIN RESET  RESET




#include "stm32f407.xx_gpio_driver.h"

#endif    /* INC_STM32F407XX_H */
