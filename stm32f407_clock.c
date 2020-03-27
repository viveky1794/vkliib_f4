

void ConfigRCC(void)
{
	RCC->CR &= RBIT(24); // PLLON Disable

	RCC->CR |= SBIT(16); // set external Clock
	while(!CBIT(RCC->CR,17)); // check ready flag

	// These bits can only enable when PLL is disable
	// VCO input frequency = PLL input clock frequency / PLLM
	// VCO input frequency = 8MHz/2 = 2MHz
	RCC->PLLCFGR |= SBIT(4);

	// VCO output frequency = VCO input frequency × PLLN
	// VCO output frequency = 2MHz * 50 = 100MHz
	RCC->PLLCFGR |= SBIT(7);
	RCC->PLLCFGR |= SBIT(10);
	RCC->PLLCFGR |= SBIT(11);
	RCC->PLLCFGR &= RBIT(12);
	RCC->PLLCFGR &= RBIT(13);
	RCC->PLLCFGR &= RBIT(14);

	// PLL output clock frequency = VCO frequency / PLLP
	// PLL output clock frequency = 100MHz/2 = 50MHz
	// This Time clock is running at 50 Mhz
	RCC->PLLCFGR &= RBIT(16);
	RCC->PLLCFGR &= RBIT(17);

	RCC->CR |= SBIT(24); // PLLON enable
	RCC->CFGR |= SBIT(1); // PLL selected as system clock

	while(! CBIT( (RCC->CFGR),3) );

	RCC->CFGR &= RBIT(7);
	RCC->CFGR &= RBIT(12);
	RCC->CFGR &= RBIT(15);

}
