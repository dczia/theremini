#define F_CPU 20000000

#include <atmel_start.h>
#include <util/delay.h>

extern volatile uint8_t measurement_done_touch;
extern volatile uint8_t LED_PWM[6];
extern volatile uint16_t timeTicks;

// Logarithmic brightness levels
const uint8_t pwm_log[] = {30,43,59,78,102,137,196,255};

KEYPRESS keyPress[5] = { 0 };
CAPKEY lastKey = KEY_NONE;

int main(void){
	
	/* Initializes MCU, drivers and middleware */
	system_init();
	touch_init();
	
	I2C_0_slave_init();
	
	cpu_irq_enable(); /* Global Interrupt Enable */


	LED1_set_level(true);
	_delay_ms(50);
	LED2_set_level(true);
	_delay_ms(50);
	LED3_set_level(true);
	_delay_ms(50);
	LED4_set_level(true);
	_delay_ms(50);
	LED5_set_level(true);
	_delay_ms(50);
	LED6_set_level(true);
	_delay_ms(200);
	
	LED1_set_level(false);
	_delay_ms(50);
	LED2_set_level(false);
	_delay_ms(50);
	LED3_set_level(false);
	_delay_ms(50);
	LED4_set_level(false);
	_delay_ms(50);
	LED5_set_level(false);
	_delay_ms(50);
	LED6_set_level(false);
	_delay_ms(50);

	TIMER_0_init();
	
	LED_PWM[0] = 14;
	LED_PWM[1] = 14;
	LED_PWM[2] = 14;
	LED_PWM[3] = 14;
	LED_PWM[4] = 14;
	LED_PWM[5] = 14;
	
	RUNMODE mode = MODE_SPOOLING;
	RUNMODE oldMode = MODE_SPOOLING;
	bool touching = false;
	bool changed = false;
	
	uint8_t step = 0;
	uint8_t delay = 0;
	uint8_t delayTop = 100;
	uint8_t counter = 0;
	uint8_t side = 0;

	/* Replace with your application code */
	while (1) {
		
		touch_process();
		if(measurement_done_touch == 1){
			////touchCheck(&touching, &changed);
			if((get_sensor_state(KEY_D) & KEY_TOUCHED_MASK) != 0){
				keyPress[KEY_D].touched = true;
				touching = true;
			}
			else{
				if(keyPress[KEY_D].touched){
					keyPress[KEY_D].touched = false;
					keyPress[KEY_D].latched = true;
					changed = true;
					lastKey = KEY_D;
					mode = MODE_SPOOLING;
				}
			}
			
			if((get_sensor_state(KEY_C) & KEY_TOUCHED_MASK) != 0){
				keyPress[KEY_C].touched = true;
				touching = true;
			}
			else{
				if(keyPress[KEY_C].touched){
					keyPress[KEY_C].touched = false;
					keyPress[KEY_C].latched = true;
					changed = true;
					lastKey = KEY_C;
					mode = MODE_HAZARDS;
				}
			}
			
			if((get_sensor_state(KEY_Z) & KEY_TOUCHED_MASK) != 0){
				keyPress[KEY_Z].touched = true;
				touching = true;
			}
			else{
				if(keyPress[KEY_Z].touched){
					keyPress[KEY_Z].touched = false;
					keyPress[KEY_Z].latched = true;
					changed = true;
					lastKey = KEY_Z;
					mode = MODE_FLICKER;
				}
			}
			
			if((get_sensor_state(KEY_I) & KEY_TOUCHED_MASK) != 0){
				keyPress[KEY_I].touched = true;
				touching = true;
			}
			else{
				if(keyPress[KEY_I].touched){
					keyPress[KEY_I].touched = false;
					keyPress[KEY_I].latched = true;
					changed = true;
					lastKey = KEY_I;
					mode = MODE_RANDOM;
				}
			}
			
			if((get_sensor_state(KEY_A) & KEY_TOUCHED_MASK) != 0){
				keyPress[KEY_A].touched = true;
				touching = true;
			}
			else{
				if(keyPress[KEY_A].touched){
					keyPress[KEY_A].touched = false;
					keyPress[KEY_A].latched = true;
					changed = true;
					lastKey = KEY_A;
					mode = MODE_REVERSE_SPOOLING;
				}
			}
		}

		if(!touching){
			if(changed){
				// Change mode
				changed = false;
				for(uint8_t i = 0; i < 6; i++){
					LED_PWM[i] = 14;
				}
				
				counter = 0;
				delay = 0;
				step = 0;
				
				if(oldMode == mode){
					delayTop = delayTop / 2;
					if(delayTop < 8){
						delayTop = 100;
					}
				}
				oldMode = mode;
			}
			
			// Update animation
			switch(mode){
				case MODE_SPOOLING:
					if(delay == 0){
						switch(step){
							case 0:
							LED_PWM[2] = 0;
							LED_PWM[3] = 0;
						
							LED_PWM[0] = 184;
							LED_PWM[5] = 184;
							step = 1;
							delay = delayTop;
							break;
							case 1:
							LED_PWM[0] = 0;
							LED_PWM[5] = 0;
						
							LED_PWM[1] = 184;
							LED_PWM[4] = 184;
							step = 2;
							delay = delayTop;
							break;
							case 2:
							LED_PWM[1] = 0;
							LED_PWM[4] = 0;
						
							LED_PWM[2] = 184;
							LED_PWM[3] = 184;
							step = 0;
							delay = delayTop;
							break;
						}
					}
					else{
						delay--;
					}
				
					break;
				case MODE_HAZARDS:
					if(delay == 0){
						if((counter % 2) == 0){
							if(side == 0){
								LED_PWM[0] = 14;
								LED_PWM[1] = 14;
								LED_PWM[2] = 14;
								LED_PWM[3] = 184;
								LED_PWM[4] = 184;
								LED_PWM[5] = 184;
								side = 1;
							}
							else{
								LED_PWM[0] = 184;
								LED_PWM[1] = 184;
								LED_PWM[2] = 184;
								LED_PWM[3] = 14;
								LED_PWM[4] = 14;
								LED_PWM[5] = 14;
								side = 0;
							}
						}
						counter++;
						delay = delayTop;
					}
					delay--;
					break;
				case MODE_FLICKER:	
					if((delay == 0)){	
						for(uint8_t i = 0; i < 6; i++){
							if(i == step){
								LED_PWM[i] = 184;
							}
							else{
								LED_PWM[i] = 14;
							}
						}
						step++;
						if(step > 5){
							step = 0;
						}
						delay = delayTop;
					}
					else{
						delay--;
					}
					break;
				case MODE_RANDOM:
					if(delay == 0){
						LED_PWM[0] = rand() % 184;
						LED_PWM[1] = rand() % 184;
						LED_PWM[2] = rand() % 184;
						LED_PWM[3] = rand() % 184;
						LED_PWM[4] = rand() % 184;
						LED_PWM[5] = rand() % 184;
						delay = delayTop;
					}
					else{
						delay--;
					}
					break;
				case MODE_REVERSE_SPOOLING:
					if(delay == 0){
						switch(step){
							case 0:
								LED_PWM[1] = 0;
								LED_PWM[4] = 0;
											
								LED_PWM[0] = 184;
								LED_PWM[5] = 184;
								step = 1;
								delay = delayTop;
								break;
							case 1:
								LED_PWM[0] = 0;
								LED_PWM[5] = 0;
								
								LED_PWM[2] = 184;
								LED_PWM[3] = 184;
								
								step = 2;
								delay = delayTop;
								break;
							case 2:
								LED_PWM[2] = 0;
								LED_PWM[3] = 0;

								LED_PWM[1] = 184;
								LED_PWM[4] = 184;
								step = 0;
								delay = delayTop;
								break;
						}
					}
					else{
						delay--;
					}
					break;
			}
		}
		else{
			touching = false;
			// Mode is about to change, light up all the LEDs
			for(uint8_t i = 0; i < 5; i++){
				LED_PWM[i] = 184;
			}
			_delay_ms(20);
		}
		
		_delay_ms(1);

	}
}

