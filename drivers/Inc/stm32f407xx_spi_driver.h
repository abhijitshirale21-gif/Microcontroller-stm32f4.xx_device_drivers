/*
 * stm32f407xx_spi_driver.h
 *
 *  Created on: Aug 19, 2026
 *      Author: Acer
 */

#ifndef INC_STM32F407XX_SPI_DRIVER_H_
#define INC_STM32F407XX_SPI_DRIVER_H_



#include"stm32f407xx.h"

typedef struct
{
	uint8_t SPI_DevieMode;            /*!< possible values form @SPI_DEvieMOde */
	uint8_t SPI_BusConfig;            /*!< possible values form @SPI_Bus COnfig   */
	uint8_t SPI_Sclkspeed;            /*!< possible values form @SPI_Sclkspeed  */
	uint8_t SPI_DFF;                  /*!< possible values form @SPI_DFF  */
	uint8_t SPI_CPOL;                 /*!< possible values form @SPI_CPOL  */
	uint8_t SPI_CPHA;                 /*!< possible values form @SPI_CPHA  */
	uint8_t SPI_SSM;                  /*!< possible values form @SPI_SSM */

}SPI_Pin_Config_t;

typedef struct
{
	SPI_RegDef_t*pGPIOx;                /*! THis hold the base addresses of SPI ports which the port belongs >*/
	SPI_Pin_Config_t SPI_PinConfig;    /*! This hold the SPI pin Configuration */

}SPI_Handle_t;



/****************************************************************************************************************************
 *                                       API Supported By this Drivers
 *For more Information About the ApIs Check the Function definitions
 ******************************************************************************************************************************/

/* peripheral clock Setup*/
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx , uint8_t  ENorDI);


/* Init and DeInit*/

void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);


/*/
 * Data Send ANd Receives
 */
void SPI_SendData(SPI_RegDef_t *pSPIx,uint8_t *pTxBuffer,uint32_t Len);

void SPI_ReceiveData(SPI_RegDef_t *pSPIx,uint8_t *pTxBuffer,uint32_t Len);


//IRQ configuration and ISR handling
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle);




#endif /* INC_STM32F407XX_SPI_DRIVER_H_ */
