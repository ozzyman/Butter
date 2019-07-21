#include <atmel_start.h>
#include <usart_basic.h>
#include <adc_basic.h>
#include <util/delay.h>

int main(void)
{
uint8_t character;

	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	USART_0_init();
	USART_0_enable();

	/* Replace with your application code */
	while (1) {
		character = USART_0_read();
		USART_0_write(character);
		LED_set_level(true);
		_delay_ms(1);
		LED_set_level(false);
		_delay_ms(1);
	}
}
