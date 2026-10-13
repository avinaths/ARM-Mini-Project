
#define l 1<<20
volatile unsigned int stop_request = 0;

void EINT0_ISR(void) __irq{
	EXTINT=0x1;
	 stop_request = 1;
	VICVectAddr=0;
}
void EINT0_init(){
	 PINSEL1 =0x01;
	VICIntSelect=0;
	
	VICVectCntl0=(0x20)|14;
	VICVectAddr0=(unsigned long)EINT0_ISR;
	
	EXTMODE=0x1;
	EXTPOLAR=0;
	
	VICIntEnable=1<<14;
}
