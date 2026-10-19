/*
 * 008spi_cmd_handling.c
 *
 *  Created on: Oct 18, 2026
 *      Author: Acer
 */


#include"stm32f407xx.h"

#include <string.h>




//command codes
#define COMMAND_LED_CTRL               0x50
#define COMMAND_SENDOR_READ            0x51
#define COMMAND_LED_READ               0x052
#define COMMAND_PRINT                  0x53
#define COMMAND_ID_READ                0x54

#define LED_ON   1
#define LED_OFF  0


//Arduino analaog pins

#define ANALOG_PIN0          0
#define ANALOG_PIN1          1
#define ANALOG_PIN2          2
#define ANALOG_PIN3          3
#define ANALOG_PIN4          4



//arduino led
#define LED_PIN  9

void delay(void)
{

	for(uint32_t  i = 0;  i < 5000000/2;  i ++);
}

/*
PB14--------> SPI@_MISO
PB15 ------->SPI2+MOSI
PB13-------->SPI2_SCLK
PB12-------->SPI2_NSS
ALT function mode :5
*/

void SPI2_GPIOInits(void)
{
	GPIO_Handle_t SPIPins;

	SPIPins.pGPIOx = GPIOB;
	SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIPins.GPIO_PinConfig.GPIO_AltFunMode = 5;
	SPIPins.GPIO_PinConfig.GPIO_PinOpType = GPIO_OP_TYPE_PP;
	SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//SCLK
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
	GPIO_Init(&SPIPins);

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	GPIO_Init(&SPIPins);

	//MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;
	//GPIO_Init(&SPIPins);


	//NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GPIO_Init(&SPIPins);


}
void GPIO_ButtonInit(void)
{
	GPIO_Handle_t GPIOBtn;

	//this is btn gpio configuration
	GPIOBtn.pGPIOx = GPIOA;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GPIOBtn);

}

void SPI2_Inits(void)
{

	SPI_Handle_t SPI2handle;

	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV32;
	SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_DI; //Hardware slave management enabled for NSS pin

	SPI_Init(&SPI2handle);
}

uint8_t SPI_VerifyResponse(uint8_t ackbyte)
{
	if(ackbyte == 0xF5)
	{

		//ack
		return 1;
	}
	return 0;

}





int main(void)
{
	uint8_t dummy_write = 0xff;
	uint8_t dummy_read;
	char user_data[] = "An Arduino Uno board is best suited for beginners who have just started using microcontrollers, on the other hand, Arduino Mega board is for enthusiasts who require a lot of I/O pins for their projects";

	GPIO_ButtonInit();

	//this function is used to initialize the GPIO pins to behave as SPI2 pins
	SPI2_GPIOInits();

	//This function is used to initialize the SPI2 peripheral parameters
	SPI2_Inits();

	/*
	* making SSOE 1 does NSS output enable.
	* The NSS pin is automatically managed by the hardware.
	* i.e when SPE=1 , NSS will be pulled to low
	* and NSS pin will be high when SPE=0
	*/
	SPI_SSOEConfig(SPI2,ENABLE);

	while(1)
	{
		//wait till button is pressed
		while( ! GPIO_ReadFromInputpin(GPIOA,GPIO_PIN_NO_0) );

		//to avoid button de-bouncing related issues 200ms of delay
		delay();

		//enable the SPI2 peripheral
		SPI_PeripheralControl(SPI2,ENABLE);


		//1 CMD_LED CTRL        <pin no(1)>      < value(1)>

		uint8_t commandcode  = COMMAND_LED_CTRL;
		uint8_t ackbyte;
		uint8_t args[2];

		// Remember
		//in spi communication when master or slave sends 1 byte it also recive 1 byte in return

		//send command
		SPI_SendData(SPI2,&commandcode,1);

		//The transmission of 1 byte resulted 1 garbage byte collection in rx buffer of the mastrer flag is set.so do the dummy read and clear the flag.

		// do dummy read to the clear off the RXNE
		SPI_ReceiveData(SPI2, &dummy_read, 1);


		//send some dummy bits (1 byte) to fetch the response from the slave
		SPI_SendData(SPI2 ,&dummy_write ,1);

		//Read ack byte received
		SPI_ReceiveData(SPI2, &ackbyte, 1);

		SPI_VerifyResponse(ackbyte);

		if ( SPI_VerifyResponse(ackbyte))
			 {
			// send arguments

			args[0] = LED_PIN;
			args[1] = LED_ON;

			//send the arguments
			SPI_SendData(SPI2 ,args ,2);

		}




		//first send length information
		uint8_t dataLen = strlen(user_data);
		SPI_SendData(SPI2,&dataLen,1);

		//to send data
		SPI_SendData(SPI2,(uint8_t*)user_data,strlen(user_data));

		//lets confirm SPI is not busy
		while( SPI_GetFlagStatus(SPI2,SPI_BUSY_FLAG) );

		//Disable the SPI2 peripheral
		SPI_PeripheralControl(SPI2,DISABLE);
	}

	return 0;

}
