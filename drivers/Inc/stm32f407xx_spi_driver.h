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
	uint8_t SPI_DeviceMode;            /*!< possible values form @SPI_DEvieMOde */
	uint8_t SPI_BusConfig;            /*!< possible values form @SPI_Bus COnfig   */
	uint8_t SPI_Sclkspeed;            /*!< possible values form @SPI_Sclkspeed  */
	uint8_t SPI_DFF;                  /*!< possible values form @SPI_DFF  */
	uint8_t SPI_CPOL;                 /*!< possible values form @SPI_CPOL  */
	uint8_t SPI_CPHA;                 /*!< possible values form @SPI_CPHA  */
	uint8_t SPI_SSM;                  /*!< possible values form @SPI_SSM */

}SPI_Pin_Config_t;

typedef struct
{
	SPI_RegDef_t*pSPIx;                /*! THis hold the base addresses of SPI ports which the port belongs >*/
	SPI_Pin_Config_t SPI_PinConfig;    /*! This hold the SPI pin Configuration */

}SPI_Handle_t;


/*@SPI DeviceMode
 *
 */
#define SPI_DEVICE_MODE_MASTER     1
#define SPI_DEVICE_MODE_SLAVE      0

/*
 * @SPI_BusConfig
 *
 */

#define SPI_BUS_CONFIG_FD                1
#define SPI_BUS_CONFIG_HD                2
#define SPI_BUS_CONFIG_SIMPLEX_TXONLY    3
#define SPI_BUS_CONFIG_SIMPLEX_RxONLY    4

/*
 * @SPI_SclkSpeed
 *
 */
#define SPI_SCK_SPEED_DIV2                   0
#define SPI_SCK_SPEED_DIV4                   1
#define SPI_SCK_SPEED_DIV8                   2
#define SPI_SCK_SPEED_DIV16                  3
#define SPI_SCK_SPEED_DIV32                  4
#define SPI_SCK_SPEED_DIV64                  5
#define SPI_SCK_SPEED_DIV128                 6
#define SPI_SCK_SPEED_DIV256                 7

/*
 * @SPI_DFF
 *
 */
#define SPI_DFF_8BITS         0
#define SPI_DFF_16BITS        1

/*
 * @CPOL
 */

#define SPI_CPOL_HIGH 1
#define SPI_CPOL_LOW  0

/*
 * @CPHA
 *
 */
#define SPI_CPHA_HIGH 1
#define SPI_CPHA_LOW  0


/*
 * @SPI_SSM
 */

#define SPI_SSM_EN     1
#define SPI_SSM_DI     0



#define SPI_TXE_FLAG   (1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG  (1 << SPI_SR_RXNE)
#define SPI_BSY_FLAG   (1 << SPI_SR_BSY)



/****************************************************************************************************************************
 *                                       API Supported By this Drivers
 *For more Information About the ApIs Check the Function definitions
 ******************************************************************************************************************************/

/* peripheral clock Setup*/
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx , uint8_t  ENorDI);
void SPI_SSIConfig(SPI_RegDef_t *pSPIx , uint8_t  ENorDI);
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx , uint8_t  ENorDI);

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


// other peripherals control APIs

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx,uint8_t EnOrDi);




#endif /* INC_STM32F407XX_SPI_DRIVER_H_ */
