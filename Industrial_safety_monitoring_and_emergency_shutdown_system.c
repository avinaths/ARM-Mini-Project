#include <lpc21xx.h>
#include "IR_sensor.h"
#include "lcd_interface_numeric.h"
#include "EINT_Interrupt.h"
#include "UART.h"

#define MOTORON 1<< 11
#define MOTOROFF 1<<12
#define LED   1<< 14

int main()
{
    unsigned int last_state = 2;
    unsigned int state;

    IODIR0 |= MOTORON |MOTOROFF | LED;
	 IOCLR0=MOTOROFF;
	 //IOSET0|= LED;
    lcd_init();
    EINT0_init();
	 uart_init();
    lcd_cmd(0x80);	
    
	 uart_str("Industrial safety monitoring and emergency shutdown system ");
	lcd_title("Industrial safety monitoring and emergency shutdown system");
    while (1)
    {
        if (stop_request)
        {
            stop_request = 0;
            IOCLR0|= MOTORON;   // Motor OFF
            IOCLR0|= LED;     // LED ON
				//IOSET0= 1<<11;
				//IOCLR0=1<<14;
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_str("MOTOR STOP");
            delay(1000);   
				uart_str(" MOTOR STOP");
            last_state = 2;   
        }
        else
        {
            state = ir_sense();
            if (state != last_state)
            {
                lcd_cmd(0x01);
                lcd_cmd(0x80);

                if (state)
                {
						  lcd_str("MOTOR OFF");
                    IOCLR0|= MOTORON;
                    IOCLR0|= LED;
							uart_str(" MOTOR OFF");
                }
                else
                {
						  lcd_str("MOTOR ON");
                    IOCLR0|= MOTORON;
                    IOSET0|= LED;
						 uart_str(" MOTOR ON");
                }

                last_state = state;
            }
        }
    }
}
