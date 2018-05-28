#include "LPC11XX.H"
#define LED1_ON()  (LPC_GPIO2->DATA &= ~(1<<0)) 	// ?????P1.0?LED
#define LED1_OFF() (LPC_GPIO2->DATA |= (1<<0)) 		// ?????P1.0?LED
#define LED2_ON()  (LPC_GPIO2->DATA &= ~(1<<1)) 	// ?????P1.1?LED
#define LED2_OFF() (LPC_GPIO2->DATA |= (1<<1)) 		// ?????P1.1?LED
#define LED3_ON()  (LPC_GPIO2->DATA &= ~(1<<2)) 	// ?????P1.0?LED
#define LED3_OFF() (LPC_GPIO2->DATA |= (1<<2)) 		// ?????P1.0?LED
#define LED4_ON()  (LPC_GPIO2->DATA &= ~(1<<3)) 	// ?????P1.0?LED
#define LED4_OFF() (LPC_GPIO2->DATA |= (1<<3)) 		// ?????P1.0?LED
#define LED5_ON()  (LPC_GPIO2->DATA &= ~(1<<4)) 	// ?????P1.0?LED
#define LED5_OFF() (LPC_GPIO2->DATA |= (1<<4)) 		// ?????P1.0?LED
#define LED6_ON()  (LPC_GPIO2->DATA &= ~(1<<5)) 	// ?????P1.0?LED
#define LED6_OFF() (LPC_GPIO2->DATA |= (1<<5)) 		// ?????P1.0?LED
#define LED7_ON()  (LPC_GPIO2->DATA &= ~(1<<6)) 	// ?????P1.0?LED
#define LED7_OFF() (LPC_GPIO2->DATA |= (1<<6)) 		// ?????P1.0?LED
#define LED8_ON()  (LPC_GPIO2->DATA &= ~(1<<7)) 	// ?????P1.0?LED
#define LED8_OFF() (LPC_GPIO2->DATA |= (1<<7)) 		// ?????P1.0?LED
int i;
void LedInit(void)
{
	int i;
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); //IOCON时钟使能
	LPC_IOCON->PIO2_0 &= ~0x07;  //2.0口  初始化
	LPC_IOCON->PIO2_0 |= 0x00; //2.0口设置为GPIO
	LPC_IOCON->PIO2_1 &= ~0x07;	
	LPC_IOCON->PIO2_1 |= 0x00; 
	LPC_IOCON->PIO2_2 &= ~0x07;	
	LPC_IOCON->PIO2_2 |= 0x00; 
	LPC_IOCON->PIO2_3 &= ~0x07;	
	LPC_IOCON->PIO2_3 |= 0x00; 
	LPC_IOCON->PIO2_4 &= ~0x07;	
	LPC_IOCON->PIO2_4 |= 0x00; 
	LPC_IOCON->PIO2_5 &= ~0x07;	
	LPC_IOCON->PIO2_5 |= 0x00; 
	LPC_IOCON->PIO2_6 &= ~0x07;	
	LPC_IOCON->PIO2_6|= 0x00; 
	LPC_IOCON->PIO2_7 &= ~0x07;	
	LPC_IOCON->PIO2_7 |= 0x00; 
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);     
	for(i=0;i<8;i++){
	LPC_GPIO2->DIR |= (1<<i); // 
	LPC_GPIO2->DATA |= (1<<i); // 
	
	}
}
/*void LeedInit()
{
	LPC_SYSCON->SYSAHBCLKCTRL |=(1<<16);
	LPC_IOCON->PIO2_0&=~0x07;
	LPC_IOCON->PIO2_0|=0x00;
	LPC_SYSCON->SYSAHBCLKCTRL&=~(1<<16);
	LPC_SYSCON->SYSAHBCLKCTRL|=(1>>6);
	LPC_GPIO2->DIR|=LED;
	LPC_GPIO2->DATA|=LED;
}*/



void T32B1_Init(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL|=(1<<10);//使能时钟
	LPC_TMR32B1->IR=0x01;
	LPC_TMR32B1->MCR=0X04;
}


void T32B1_DelayMs(uint16_t ms)
{
	LPC_TMR32B1->TCR=0x02;//清0
	
	LPC_TMR32B1->PR=0;
	
	LPC_TMR32B1->MR0= ms*(SystemCoreClock/1000);
	LPC_TMR32B1->TCR=0x01;//启动定时器
	while(LPC_TMR32B1->TCR&0X01);
}


int main()
{
	LedInit();
	T32B1_Init();
	while(1)
	{
		for(i=0;i<8;i++)
		{
			T32B1_DelayMs(500);
			LPC_GPIO2->DATA &=~ (1<<i); // 
			T32B1_DelayMs(500);
			LPC_GPIO2->DATA|= (1<<i);		
		}
		

}
}