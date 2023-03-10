#include "stm32f407xx.h"

#define BTN_PRESSED 0
void delay(void)
{
	for (uint32_t i=0; i<250000; i++);
}

int main(void)
{
	GPIO_Handle_t GpioLed, GpioBtn;

	memset(&GpioLed, 0, sizeof(GpioLed));
	memset(&GpioBtn, 0, sizeof(GpioBtn));

	GpioLed.pGPIOx = GPIOD;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioLed.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClkCtrl(GPIOD, ENABLE);
	GPIO_Init(&GpioLed);


	GpioBtn.pGPIOx = GPIOD;
	GpioBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GpioBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GpioBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GpioBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	GPIO_PeriClkCtrl(GPIOD, ENABLE);
	GPIO_Init(&GpioBtn);

	GPIO_IRQPriorityConfig(IRQ_NO_EXIT9_5, NVIC_TRQ_PRIO15);
	GPIO_IRQInterruptConfig(IRQ_NO_EXIT9_5, ENABLE);


	return 0;
}
void EXTI9_5_IRQHandler(void)
{
	delay();
	GPIO_IRQHandling(GPIO_PIN_NO_5);
	GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
}
