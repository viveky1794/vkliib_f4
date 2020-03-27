



void toggleLED(uint8_t pin)
{
	// General purpose output mode
	GPIOD->MODER |= SBIT((2*pin));
	GPIOD->MODER &= RBIT((2*pin)+1);

	// Output Push Pull
	GPIOD->OTYPER &= RBIT(pin);

	// Medium Speed
	GPIOD->OSPEEDR |= SBIT((2*pin));
	GPIOD->OSPEEDR &= RBIT(((2*pin)+1));

	while(1)
	{
		GPIOD->ODR	|= SBIT(pin);
		for(uint32_t i=0;i<100000;i++);
		GPIOD->ODR	&= RBIT(pin);
		for(uint32_t i=0;i<100000;i++);
	}
}
