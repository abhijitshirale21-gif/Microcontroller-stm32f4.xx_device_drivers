/*
 * stm32f407_spi_driver.c
 *
 *  Created on: Aug 19, 2026
 *      Author: Acer
 */


#include "stm32f407xx_spi_driver.h"
static void spi_tx_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle);


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
/******************************************************************************************************************************
 * @fn                  - SPI_ReciveData
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

void SPI_ReciveData(SPI_RegDef_t *pSPIx, uint8_t *pRXNEBuffer, uint32_t Len)
{
        while(Len > 0)
	{
		//wait until RXNE is SET
		while(SPI_GetFlagStatus(pSPIx,SPI_RXNE_FLAG) == FLAG_RESET)  ;

		//check the dff bit in CR1
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			// 16 bit DFF
			//load the data into the DR
			   *((uint16_t *)pRXNEBuffer)= pSPIx-> DR;

			Len--;
			Len--;
			 *(uint16_t *)pRXNEBuffer++;

		}else
		{
			//8but DFF
			   *(pRXNEBuffer)= pSPIx-> DR;
			Len--;
			pRXNEBuffer++;

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

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle,uint8_t *pTxBuffer,uint32_t Len)
{
	uint8_t state = pSPIHandle->Txstate;

	if( state != SPI_BUSY_IN_TX)
	{

	//1.save the TX Buffer address and the len information in some global variables

	pSPIHandle ->pTxBuffer = pTxBuffer;
	pSPIHandle ->Txlen  = Len;


	//2. mark the spi states busy on transmission  so that
	//no other code ccan take over same spi peripheral ; until transmission is over*/
	pSPIHandle->Txstate = SPI_BUSY_IN_TX;


	//3.enable the TXEIE control bit to get interrupt whenever TXW flag is set in SR
	pSPIHandle->pSPIx ->CR2 |= (1 << SPI_CR2_TXEIE);

	//data transmission will be handle by the isr code
	}
	return state;


}
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle,uint8_t *pRxBuffer,uint32_t Len)
{

	uint8_t state = pSPIHandle->Rxstate;

	if( state != SPI_BUSY_IN_RX)
	{

	//1.save the TX Buffer address and the len information in some global variables

	pSPIHandle ->pRxBuffer = pRxBuffer;
	pSPIHandle ->Rxlen  = Len;


	//2. mark the SPI states busy on transmission  so that
	//no other code can take over same spi peripheral ; until transmission is over*/
	pSPIHandle->Rxstate = SPI_BUSY_IN_RX;


	//3.enable the TXEIE control bit to get interrupt whenever TXW flag is set in SR
	pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_RXNEIE);

	//data transmission will be handle by the isr code
	}
	return state;

}


void SPI_IRQHandling(SPI_Handle_t *pSPIHandle)
{

	uint8_t temp1,temp2;
	temp1 = pSPIHandle->pSPIx->SR = (1 >> SPI_SR_TXE);
	temp2 = pSPIHandle->pSPIx->CR2 = (1 >> SPI_CR2_TXEIE);

	if(temp1 && temp2)
	{
		//Handle TXE
		SPI_tx_interrupt_handle(pSPIHandle);
	}

	//Check for RXNE

	temp1 = pSPIHandle->pSPIx->SR = (1 >> SPI_SR_RXNE);
	temp2 = pSPIHandle->pSPIx->CR2 = (1 >> SPI_CR2_RXNEIE);

	if(temp1 && temp2)
	{
		//Handle RXE
		SPI_rxne_interrupt_handle(pSPIHandle);
	}

	// Check for Over FLag


		temp1 = pSPIHandle->pSPIx->SR = (1 >> SPI_SR_OVR);
		temp2 = pSPIHandle->pSPIx->CR2 = (1 >> SPI_CR2_ERRIE);

		if(temp1 && temp2)
		{
			//Handle RXE
			SPI_ovr_err_interrupt_handle(pSPIHandle);
		}

}


//SOME HELPER FUNCTION IMPLEMENTATION
static void spi_tx_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	if(pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF))
			{
				// 16 bit DFF
				//load the data into the DR
		pSPIHandle->pSPIx->DR = *((uint16_t *)pSPIHandle->pTxBuffer);
		pSPIHandle -> Txlen--;
		pSPIHandle -> Txlen--;
	   *(uint16_t *)pSPIHandle->pTxBuffer++;

			}else
			{
				//8but DFF
				pSPIHandle->pSPIx->DR = pSPIHandle->pTxBuffer;
				pSPIHandle -> Txlen--;
				pSPIHandle->pTxBuffer++;

			}
	if(pSPIHandle->Txlen)
	{
		//txlen is zero so close the spi transmission and inform and application that
		// tx is over
		//this prevent the interrupt from setting up the txE flag
		SPI_CloseTransmission(pSPIHandle);
		SPI_ApplicationEventcallback(pSPIHandle,SPI_EVENT_TX_CMPLT);

	}

}
static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	//do Rx as per the DFF
	if(pSPIHandle->pSPIx->CR1 & (1 << 11))  // SPI_CR1_DFF is define in set value is 11
				{
					// 16 bit DFF
					//load the data into the DR

		    pSPIHandle->pSPIx->DR = *((uint16_t *)pSPIHandle->pRxBuffer);
			pSPIHandle -> Rxlen-=2;

			pSPIHandle -> pRxBuffer--;
			pSPIHandle -> Rxlen--;

				}else
				{
					//8but DFF
					pSPIHandle->pSPIx->DR = pSPIHandle->pRxBuffer;
					pSPIHandle -> Rxlen--;
					pSPIHandle->pRxBuffer++;

				}
		if(pSPIHandle->Rxlen)
		{
			//txlen is zero so close the spi transmission and inform and application that
			// tx is over
			//this prevent the interrupt from setting up the txE flag
			SPI_CloseReception(pSPIHandle);
			SPI_ApplicationEventcallback(pSPIHandle,SPI_EVENT_RX_CMPLT);

		}
}
static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
	uint8_t temp;

	// clear the ovr flag
	if(pSPIHandle->Txstate != SPI_BUSY_IN_TX)
	{
		temp = pSPIHandle-> pSPIx->DR;
		temp = pSPIHandle-> pSPIx->SR;
	}
	(void)temp;

		//2.inform the appplication
		SPI_ApplicationEventcallback(pSPIHandle,SPI_EVENT_OVR_ERR);



}

void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle)
{
	    pSPIHandle->pSPIx->CR2 & (1 << SPI_CR1_DFF);
		pSPIHandle->pTxBuffer = NULL;
		pSPIHandle->Txlen = 0;
		pSPIHandle->Txstate = SPI_READY;
}
void SPI_CloseReception(SPI_Handle_t *pSPIHandle)
{
			pSPIHandle->pSPIx->CR2 & ~(1 << SPI_CR2_RXNEIE);
			pSPIHandle->pRxBuffer = NULL;
			pSPIHandle-> Rxlen= 0;
			pSPIHandle->Rxstate = SPI_READY;
	}

void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx)
{
	        uint8_t temp;
			temp =  pSPIx->DR;
			temp =  pSPIx->SR;
			(void)temp;


}

__weak void SPI_ApplicationEventcallback(SPI_Handle_t *pSPIHandle,uint8_t AppEv)
{
	//This is a weak implementation the user application may override this function.
}

