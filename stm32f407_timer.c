// TODO: make general Time delay funcation.
//     : Explore other General and Advance Funcation.


void configTIM6(void)
{
  // Out Clock is 50MHz
  // Get Interrupt at every 1 sec.
  // it is developer reposibility to clear the interrupt in status Register.
	
 // 1: Enable Peripherial Clock of Timer 
 // RCC->APB1ENR |= SBIT(4);// TIM 6  Enable Periphherial clock
  
	TIM6->PSC = 4999;
	TIM6->ARR = 5000;
	TIM6->CR1 |= SBIT(0);// Start Timer 6
  
  while(1)
  {
    if((CBIT(TIM6->SR,0))) {// bit will set every 1 sec
	TIM6->SR &= RBIT(0);
	GPIOD->ODR ^= SBIT(12);
        }
  }
  
}
