
/**
  * @brief Universal Synchronous Asynchronous Receiver Transmitter
  */

typedef struct
{
  __IO uint32_t SR;         /*!< USART Status register,                   Address offset: 0x00 */
  __IO uint32_t DR;         /*!< USART Data register,                     Address offset: 0x04 */
  __IO uint32_t BRR;        /*!< USART Baud rate register,                Address offset: 0x08 */
  __IO uint32_t CR1;        /*!< USART Control register 1,                Address offset: 0x0C */
  __IO uint32_t CR2;        /*!< USART Control register 2,                Address offset: 0x10 */
  __IO uint32_t CR3;        /*!< USART Control register 3,                Address offset: 0x14 */
  __IO uint32_t GTPR;       /*!< USART Guard time and prescaler register, Address offset: 0x18 */
} USART_TypeDef;

#define USART1              ((USART_TypeDef *) USART1_BASE)
#define USART6              ((USART_TypeDef *) USART6_BASE)
#define USART2              ((USART_TypeDef *) USART2_BASE)
#define USART3              ((USART_TypeDef *) USART3_BASE)
#define UART4               ((USART_TypeDef *) UART4_BASE)
#define UART5               ((USART_TypeDef *) UART5_BASE)



void configUSART(void)
{
	//uint32_t temp =0;

	// 1 : Set GPIO PIN for USART2
		// PA2->TX and PA3->RX
			// Enable Port A
			// Enable Alternate Functionality
			// Output push-pull (reset state)
			// Alternative Functionality register
				RCC->AHB1ENR |= SBIT(0);
				RCC->APB1ENR |= SBIT(17);// Enable USART2
				GPIOA->MODER |= SBIT(5);  // BIT[5:4]=[1:0], Alternative Functionality
				GPIOA->MODER |= SBIT(7);  // BIT[7:6]=[1:0], Alternative Functionality
				GPIOA->OSPEEDR |= SBIT(5);// BIT[5:4]=[1:0], High Speed
				GPIOA->OSPEEDR |= SBIT(7);// BIT[7:6]=[1:0], High Speed

				GPIOA->AFR[0] |= SBIT(8);
				GPIOA->AFR[0] |= SBIT(9);
				GPIOA->AFR[0] |= SBIT(10);

				GPIOA->AFR[0] |= SBIT(12);
				GPIOA->AFR[0] |= SBIT(13);
				GPIOA->AFR[0] |= SBIT(14);

	// 2 : Enable USART Peripherial Clock

		// Config Status Register(SR)
		// -----------------------------------------------
		// Bit 7 TXE: Transmit data register empty, This bit is set by hardware,
		// An interrupt is generated if the TXEIE bit =1 in the USART_CR1 register.
		// It is cleared by a write to the USART_DR register.
		// Bit 6 TC: Transmission complete, This bit is set by hardware
		// An interrupt is generated if TCIE=1 in the USART_CR1 register

		// Config Control Register 1 (CR1)
		// ------------------------------------------------
		// Reset value: 0x0000 0000
		// Bit 7 TXEIE: TXE interrupt enable
		// Bit 6 TCIE: Transmission complete interrupt enable
		// Bit 3 TE: Transmitter enable
		// Bit 2 RE: Receiver enable
			USART2->CR1 &= ~(0xFFFFFFFF);
			USART2->CR1 |= SBIT(2);
			USART2->CR1 |= SBIT(3);
			USART2->CR1 |= SBIT(6);
			USART2->CR1 |= SBIT(7);
		//---------------------------------------------------

		// Config Control Register 2 (CR2)
		// ------------------------------------------------
		// Reset value: 0x0000 0000
			USART2->CR2 &= ~(0xFFFFFFFF);

		// Config Baud rate register
		// --------------------------------------------------
		// APB1CLK = 25MHz
		// baudrate = 115200
		// BRR = APB1CLK/baudrate = 25,000,000/115200 = 217.--
		// 217 = 0xD9;
		USART2->BRR = 0xd9;

		// USART enable
		USART2->CR1 |= SBIT(13);

}//End- configUSART()

void sendCharUSART(uint8_t cdata)
{
	while(!(USART2->SR & 1<<6));
	while(!(USART2->SR & 1<<7));

	USART2->DR = cdata;
}
