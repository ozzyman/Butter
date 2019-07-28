#include <atmel_start.h>
#include <usart_basic.h>
#include <adc_basic.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>


int main(void)
{
char character;
uint8_t tx[8] = "Out ";
uint8_t rx[8];
uint8_t i, length;

	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	USART_0_init();
	USART_0_enable();
	
	/* Initialise Bluetooth module */
	/* No code here yet */
	
	/* set up port A*/
	PORTA_set_port_dir(0x01, PORT_DIR_IN);	/* set port PA0 to input */
	PORTA_set_port_dir(0xFE, PORT_DIR_OUT);	/* set all other A port pins to outputs */
	for(i=0; i<7; i++){						/* set all pins to non-inverted i.e 1 = true = +3v */
		PORTA_pin_set_inverted(i, false);	
	}
	PORTA_pin_set_inverted(7, true);		/* set PA7 to inverted because it has a P-Channel driver */
	PORTA_write_port(0x00);	/* set all port A outputs to low (0v) */
	
	sei();				/*ENABLE_INTERRUPTS*/
	
	/* Replace with your application code */
	while (1) {
		length = 0;
		character = 0x00;
		while(character != 0x0A){		/* repeat until we get a newline */
			character = USART_0_read();
			rx[length] = character;
			length++;
			if(length>7){
				length = 7;				/* avoid buffer overflow */
			}
		}

		PORTA_write_port(rx[0]);		/* send received byte to port A */

		for(i=0; i<4; i++){
			USART_0_write(tx[i]);		/* Send "Out " response to sender */
		}

		USART_0_write(PORTA_get_port_level());		/* ... and confirm output */

		for (i=0; i<length; i++){		/* clear receive buffer */
			rx[i] = 0x20;		
		}
		LED_set_level(true);			/* flash the LED */
		_delay_ms(10);
		LED_set_level(false);
	}
}

