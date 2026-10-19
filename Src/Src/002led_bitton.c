/*
 * 001led_toggle.c
 *
 *  Created on: Aug 2, 2026
 *      Author: Acer
 */
#include "stm32f407xx.h"
#define HIGH 1
#define BTN_PRESSED_HIGH 1

void delay(void)
{
	for(uint32_t i = 0; i < 50000/2; i++);
}
int main(void)
{
	GPIO_Handle_t GpioLed,GpioBtn;

	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	GpioLed.GPIO_PinConfig.GPIO_PinOpType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClockControl(GPIOD,ENABLE);
	GPIO_Init(&GpioLed);

	GpioBtn.pGPIOx = GPIOA;
		GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
		GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
		GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
		GpioBtn.GPIO_PinConfig.GPIO_PinOpType = GPIO_OP_TYPE_PP;
		GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

		GPIO_PeriClockControl(GPIOA,ENABLE);
		GPIO_Init(&GpioBtn);


	while(1)
	{
		if(GPIO_ReadFromInputpin(GPIOA,GPIO_PIN_NO_0) == BTN_PRESSED_HIGH)
		{
			delay();
		  GPIO_ToggleOutputpin(GPIOD, GPIO_PIN_NO_12);
		}

	}
	return 0;





}
/*
 * 002led_bitton.c
 *
 *  Created on: Aug 6, 2026
 *      Author: Acer
 */


