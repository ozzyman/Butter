#include <atmel_start.h>
#include <util/delay.h>
#include <usart_basic.h>

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	/* Replace with your application code */
	while (1) {
		LED_set_level(true);
		_delay_ms(100);
		LED_set_level(false);
		_delay_ms(100);
		LED_set_level(true);
		_delay_ms(100);
		LED_set_level(false);
		_delay_ms(1000);
		USART_0_init(115200);
			
	}
}
