/*
 * stm32f407.xx_gpio_driver.h
 *
 *  Created on: Jul 30, 2026
 *      Author: Acer
 */

#ifndef INC_STM32F407_XX_GPIO_DRIVER_H_
#define INC_STM32F407_XX_GPIO_DRIVER_H_

#include"stm32f407xx.h"

typedef struct
{
	uint8_t GPIO_PinNumber;           /*!< possible values form @GPIO_PIN_Numbers  */

	uint8_t GPIO_PinMode;            /*!< possible values form @GPIO_PIN_MODES  */
	uint8_t GPIO_PinSpeed;           /*!< possible values form @GPIO_PIN_SPEED  */
	uint8_t GPIO_PinPuPdControl;     /*!< possible values form @GPIO_PUPD  */
	uint8_t GPIO_PinOpType;           /*!< possible values form @GPIO_OT  */
	uint8_t GPIO_AltFunMode;

}GPIO_Pin_Config_t;

/* This is a Handle Structure of GPIO pins
 * */

typedef struct
{
	GPIO_RegDef_t*pGPIOx;                /*! THis hold the base addresses of GPIO ports which the port belongs >*/
	GPIO_Pin_Config_t GPIO_PinConfig;    /*! This hold the GPIO pin Configuration */

}GPIO_Handle_t;

/*@GPIO_PIN_Numbers
 * GPIO Pin numbers
 */
#define GPIO_PIN_NO_0         0
#define GPIO_PIN_NO_1         1
#define GPIO_PIN_NO_2         2
#define GPIO_PIN_NO_3   	  3
#define GPIO_PIN_NO_4         4
#define GPIO_PIN_NO_5         5
#define GPIO_PIN_NO_6         6
#define GPIO_PIN_NO_7         7
#define GPIO_PIN_NO_8         8
#define GPIO_PIN_NO_9         9
#define GPIO_PIN_NO_10        10
#define GPIO_PIN_NO_11        11
#define GPIO_PIN_NO_12        12
#define GPIO_PIN_NO_13        13
#define GPIO_PIN_NO_14        14
#define GPIO_PIN_NO_15        15


/*
 * @GPIO_PIN_MODES
 * GPIO pin Possible modes
 *
 */
#define GPIO_MODE_IN  		      0
#define GPIO_MODE_OUT  			  1
#define GPIO_MODE_ALTFN 		  2
#define GPIO_MODE_ANALOG 		  3
#define GPIO_MODE_IT_FT 		  4
#define GPIO_MODE_IT_RT  		  5
#define GPIO_MODE_IT_RFT 		  6


/*
 * @GPIO_OT
 *  GPIO Pin POssible  output types
 *
 */

#define GPIO_OP_TYPE_PP    0
#define GPIO_OP_TYPE_OD    1


/* @GPIO_PIN_SPEED
 * GPIO pin Possible output speed
 *
 */
#define GPIO_SPEED_LOW       0
#define GPIO_SPEED_MEDIUM    1
#define GPIO_SPEED Fast      2
#define GPIO_SPEED_HIGH      3


/*
 * @GPIO_PUPD
 * GPIO Pin pull up and pull Down Configuration macros
 *
 */

#define GPIO_NO_PUPD       0
#define GPIO_PIN_PU        1
#define GPIO_PIN_PD        2



/****************************************************************************************************************************
 *                                       API Supported By this Drivers
 *For more Information About the ApIs Check the Function definitions
 ******************************************************************************************************************************/






/* peripheral clock Setup*/
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx , uint8_t  ENorDI);



/* Init and DeInit*/

void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

// Data Read Write
uint8_t  GPIO_ReadFromInputpin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber);
uint16_t GPIO_ReadFromInputport(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputpin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber,uint8_t Value);
void GPIO_WriteToOutputport(GPIO_RegDef_t *pGPIOx,uint16_t PinNumber);
void GPIO_ToggleOutputpin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber);

//IRQ configuration and ISR handling
void GPIO_IRGConfig(uint8_t IRQNumber,uint8_t IRQPriority,uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t PinNumber);





#endif /* INC_STM32F407_XX_GPIO_DRIVER_H_ */
