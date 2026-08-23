/*
 * 006spi_tx_texting.c
 *
 *  Created on: Aug 22, 2026
 *      Author: Acer
 */


/* PB14 -> SPI2_MISO
 * PB15 -> SPI2_MOSI
 * PB13-> SPI2_SCLK
 * PB12-> SPI2_NSS
 * ALT Function mode :5
 *
 */
#include<string.h>
#include "stm32f407xx.h"


void SPI2_GPIOInits(void)

{
	GPIO_Handle_t SPIPins;

	SPIPins.GPIO_PinConfig.GPIO_PinMode ==  GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_AltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOpType==  GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;


	//SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber == GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber == GPIO_PIN_NO_15;
		GPIO_Init(&SPIPins);

	//MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber == GPIO_PIN_NO_14;
		GPIO_Init(&SPIPins);

		//NSS
		SPIPins.GPIO_PinConfig.GPIO_PinNumber == GPIO_PIN_NO_12;
			GPIO_Init(&SPIPins);






}
void SPI2_Inits(void)
{
	SPI_Handle_t SPI2handle;

	SPI2handle.SPI_PinConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPI_PinConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPI_PinConfig.SPI_Sclkspeed =  SPI_SCK_SPEED_DIV2;//gernarate sck for 8 mhz
	SPI2handle.SPI_PinConfig.SPI_DFF    = SPI_DFF_8BITS;
	SPI2handle.SPI_PinConfig.SPI_CPHA  = SPI_CPHA_LOW;
	SPI2handle.SPI_PinConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPI_PinConfig.SPI_SSM =   SPI_SSM_EN;//software slave managaement enabled for slave nss

	SPI_Init(&SPI2handle);



}

int main(void)
{

	char user_data[] ="Hello World";
	// this function is used to initilze the GPIO pins to behave at SPI2 pins
	SPI2_GPIOInits();

	// this function is used to initilze the SPI peripheral paramter
	SPI2_Inits();

	//enable the Spi2 peripherals
	SPI_PeripheralControl(SPI2,ENABLE);

	//This make signal internally high and avoid the MODF error

	SPI_SSIConfig(SPI2,ENABLE);

	//Disable the SPI peripherals
	SPI_PeripheralControl(SPI2,DISABLE);



	SPI_SendData(SPI_SendData,(uint8_t*)user_data,strlen(*user_data));

	while(1)


	return 0;

}
