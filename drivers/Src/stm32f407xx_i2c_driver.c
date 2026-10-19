/*
 * stm32f407xx_i2c_driver.c
 *
 *  Created on: Oct 19, 2026
 *      Author: Acer
 */

/*********************************************************************
 * @fn      		  - d I2C_PeripheralControl
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pI2Cx->CR1 |=(1 << I2C_CR1_PE);
		//pI2CBaseAddress-> |= I2C_CR1_PE_Bit_Mask;
	}else
	{
		pI2Cx->CR1 &= ~(1 << 0);

	}
}
/*********************************************************************
 * @fn      		  -  I2C_PeriClockControl
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
/*********************************************************************
 * @fn      		  - I2C_PeriClockControl(
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnOrDi == ENABLE)
	{
		if(pI2Cx == I2C1)
		{
			I2C1_PCLK_EN();
		}else if(pI2Cx == I2C2)
		{
			I2C2_PCLK_EN();
		}else if(pI2Cx == I2C3)
		{
			I2C3_PCLK_EN();

		}
	}
	else
	{
		//TODO
	}
}

//uint32_t RCC_GEtPLLOutputClock();
//{
//	//todo
//	return
//}
uint32_t RCC_GetPCLKValue(void)
{
	uint32_t pclk1 ,SystemClk;
	uint8_t clksrc temp;
	clksrc = ((RCC-> CFGR >> 2) & 0x3);

		if(clksrc == 0)
		{
			SystemClk = 16000000;
		}else if(clksrc ==1)
		{
			SystemClk = 8000000;
		}else if (clksrc == 2)
		{
			SystemClk  = RCC_GEtPLLOutputClock();
		}

	return pclk1
}
/*********************************************************************
 * @fn      		  -  I2C_Init
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */
void I2C_Init(I2C_Handle_t *pI2CHandle)
{
	uint32_t tempreg = 0;

	tempreg = pI2CHandle->I2C_Config.I2C_ACKControl << 10)

}
