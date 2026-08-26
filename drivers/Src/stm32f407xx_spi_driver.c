/*
 * stm32f407_spi_driver.c
 *
 *  Created on: Aug 19, 2026
 *      Author: Acer
 */


#include "stm32f407xx_spi_driver.h"


/* peripheral clock Setup*/
/******************************************************************************************************************************
 * @fn                  - SPI_PeriClockControl
 *
 * @brief                -The Function Enable or Disables Peripheral clock for the given GPIO ports
 *
 *
 * @param[in]         -  base Addresses of the gpio peripheral
 * @param[in]         - Enable or Disable macros
 *
 *
 *
 * @return           - None
 *
 * @Note           - None
 *****************************************************************************************************************************/

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx , uint8_t  ENorDI)
{
	if(ENorDI == ENABLE)
	{
		if(pSPIx ==SPI1)
		{
			SPI1_PCLK_EN();
		}else if (pSPIx ==SPI2)
		{
			SPI1_PCLK_EN();
		}else if (pSPIx ==SPI3)
		{
			SPI3_PCLK_EN();

		}
	}
	else
	{


	}
}

/* peripheral clock Setup*/
/******************************************************************************************************************************
 * @fn                  - SPI_PeriClockControl
 *
 * @brief                -The Function Enable or Disables Peripheral clock for the given GPIO ports
 *
 *
 * @param[in]         -  base Addresses of the gpio peripheral
 * @param[in]         - Enable or Disable macros
 *
 *
 *
 * @return           - None
 *
 * @Note           - None
 *****************************************************************************************************************************/


void SPI_Init(SPI_Handle_t *pSPIHandle)

{
    uint32_t tempreg = 0;

    // peripheral clock enable

	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);
    // 1. Device mode;
    tempreg |= (pSPIHandle->SPI_PinConfig.SPI_DeviceMode << 2);

    // 2. Bus configuration
    if(pSPIHandle->SPI_PinConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
    {
        // Full duplex
        tempreg &= ~(1 << 15);
        tempreg &= ~(1 << 10);
    }
    else if(pSPIHandle->SPI_PinConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
    {
        // Half duplex
        tempreg |= (1 << 15);
    }
    else if(pSPIHandle->SPI_PinConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_TXONLY)
    {
        // Simplex transmit only
        tempreg |= (1 << 15);
        tempreg |= (1 << 10);
    }

    // 3. Clock speed
    tempreg |= (pSPIHandle->SPI_PinConfig.SPI_Sclkspeed << 3);

    // 4. Data frame format
    tempreg |= (pSPIHandle->SPI_PinConfig.SPI_DFF << 11);

    // 5. CPOL
    tempreg |= (pSPIHandle->SPI_PinConfig.SPI_CPOL << 1);

    // 6. CPHA
    tempreg |= (pSPIHandle->SPI_PinConfig.SPI_CPHA << SPI_CR1_CPHA );

    pSPIHandle->pSPIx->CR1 = tempreg;
}

/******************************************************************************************************************************
 * @fn                  - SPI_DInit
 *
 * @brief                -
 *
 *
 * @param[in]         -  base Addresses of the gpio peripheral
 * @param[in]         - Enable or Disable macros
 *
 *
 *
 * @return           - None
 *
 * @Note           - None
 *****************************************************************************************************************************/
void SPI_DInit(SPI_Handle_t *pSPIHandle)
{

}




uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx , uint32_t FlagName)
{
	if(pSPIx->SR & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;


}




/* SPI_SendData*/
/******************************************************************************************************************************
 * @fn                  - SPI_SendData
 *
 * @brief                -
 *
 *
 * @param[in]         -  base Addresses of the gpio peripheral
 * @param[in]         - Enable or Disable macros
 *
 *
 *
 * @return           - None
 *
 * @Note           - None
 *****************************************************************************************************************************/

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
	while(Len > 0)
	{
		//wait until TXE is SET
		while(SPI_GetFlagStatus(pSPIx,SPI_TXE_FLAG) == FLAG_RESET)  ;

		//check the dff bit in CR1
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			// 16 bit DFF
			//load the data into the DR
			  pSPIx->DR = *((uint16_t *)pTxBuffer);
			Len--;
			Len--;
			 *(uint16_t *)pTxBuffer++;

		}else
		{
			//8but DFF
			pSPIx->DR = *pTxBuffer;
			Len--;
			pTxBuffer++;

		}


	}
}

/* SPI_SendData*/
/******************************************************************************************************************************
 * @fn                  -  SPI_PeripheralControl
 *
 * @brief                -
 *
 *
 * @param[in]         -  base Addresses of the gpio peripheral
 * @param[in]         - Enable or Disable macros
 *
 *
 *
 * @return           - None
 *
 * @Note           - None
 *****************************************************************************************************************************/
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        pSPIx->CR1 |= (1 << SPI_CR1_SPE);
    }
    else
    {
        pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
    }
}
/* SPI_SendData*/
/******************************************************************************************************************************
 * @fn                  -SPI_SSIConfig
 *
 * @brief                -
 *
 *
 * @param[in]         -
 * @param[in]         -
 *
 *
 *
 * @return           - None
 *
 * @Note           - None
 *****************************************************************************************************************************/
void SPI_SSIConfig(SPI_RegDef_t *pSPIx , uint8_t  ENorDI)
{
	 if(ENorDI == ENABLE)
	    {
	        pSPIx->CR1 |= (1 << SPI_CR1_SSI);
	    } else
	    {
	        pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
	    }
}
/* SPI_SendData*/
/******************************************************************************************************************************
 * @fn                  -  SPI_SSOEConfig
 *
 * @brief                -
 *
 *
 * @param[in]         -  base Addresses of the gpio peripheral
 * @param[in]         - Enable or Disable macros
 *
 *
 *
 * @return           - None
 *
 * @Note           - None
 *****************************************************************************************************************************/
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx , uint8_t  ENorDI)
{
	 if(ENorDI == ENABLE)
	    {
	        pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
	    } else
	    {
	        pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
	    }
}




