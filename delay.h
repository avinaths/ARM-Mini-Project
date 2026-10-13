void delay(unsigned int ms){
	T0PR=15000-1;
	T0TCR=0x01;
	while(T0TC<ms);
	T0TCR=0x3;
	T0TCR=0x0;
}
