



void configTIM6(void)
{
  // Out Clock is 50MHz
  // Get Interrupt at every 1 sec.
  // it is developer reposibility to clear the interrupt in status Register.
  
	TIM6->PSC = 4999;
	TIM6->ARR = 5000;
	TIM6->CR1 |= SBIT(0);
  
  while(1)
  {
    if((CBIT(TIM6->SR,0)))
		{
			TIM6->SR &= RBIT(0);
			GPIOD->ODR ^= SBIT(12);
		}
  }
  
}
