#include <pololu/orangutan.h>

/*
 * Giovanni Galasso
 * SENG5831 Spring 2015
 * HW3
 *
 * I had some issues getting the encoder counts to print correctly. It works fine
 * using the function below, up until the int's top number. So I tried using a bigger
 * variable and resetting the counts every time we checked for them, but going in reverse
 * came up with odd results. 
 * http://www.pololu.com/docs/0J20
 * http://www.pololu.com
 * http://forum.pololu.com
 */

int main()
{
  /*while(1)
  {
    // note that the following line could also be accomplished with:
    // int pot = analogRead(7);
    int pot = read_trimpot();    // determine the trimpot position
    int motorSpeed = pot/2-256;  // turn pot reading into number between -256 and 255
	if(motorSpeed == -256)
		motorSpeed = -255; // 256 is out of range
    set_motors(motorSpeed, motorSpeed);
  
    int ledDelay = motorSpeed;
	if(ledDelay < 0)
	  ledDelay = -ledDelay;  // make the delay a non-negative number
	ledDelay = 256-ledDelay; // the delay should be short when the speed is high

    red_led(1);       // turn red LED on
    delay_ms(ledDelay);

    red_led(0);       // turn red LED off
	delay_ms(ledDelay);
  }*/
    // Initialize the encoders and specify the four input pins.
    encoders_init(IO_D3, IO_D2, IO_D1, IO_D0);
    int16_t motorSpeed = 20;
    int forward = 1;
    int32_t rotations;
    
    lcd_init_printf();
    while(1)
    {
        if (forward == 1) {
            if (button_is_pressed(TOP_BUTTON)) {
                if (motorSpeed == 250) {
                    motorSpeed = 256;
                } else {
                    motorSpeed += 10;
                }
            } else if (button_is_pressed(BOTTOM_BUTTON)) {
                if (motorSpeed == 256) {
                    motorSpeed = 250;
                } else if(motorSpeed > 0) {
                    motorSpeed += -10;
                }
            }
            delay_ms(100);
        } else if (forward == 0) {
            if(button_is_pressed(TOP_BUTTON)) {
                if (motorSpeed == -250) {
                    motorSpeed = -255;
                } else if (motorSpeed > -250){
                    motorSpeed += -10;
                }
            } else if (button_is_pressed(BOTTOM_BUTTON)) {
                if(motorSpeed == -255) {
                    motorSpeed = -250;
                } else if (motorSpeed < 0) {
                    motorSpeed += 10;
                }
            }
            delay_ms(100);
        }
        
        //Switch motor directionw with short delay
        if(button_is_pressed(MIDDLE_BUTTON)) {
            set_motors(0, 0);
            if (forward == 1) {
                forward = 0;
            } else if (forward == 0) {
                forward = 1;
            }
            delay_ms(500);
            motorSpeed = -motorSpeed;
        }
        
        //Before setting motor speed verify we are within the right range
        if(motorSpeed < -255) {
            motorSpeed = -255; // 256 is out of range
        } else if (motorSpeed > 256) {
            motorSpeed = 256;
        }
        set_motors(motorSpeed, motorSpeed);
        
        //Read the counts for motor 1 and print to LCD.
       
        //rotations = encoders_get_counts_m1();
        //rotations += encoders_get_counts_and_reset_m1();
        //rotations = svp_get_counts_cd();
        lcd_goto_xy(0,0);
        print("Count:            ");
        lcd_goto_xy(7,0);
        print_long(encoders_get_counts_m1());
        //printf("%lu", rotations);
        lcd_goto_xy(0,1);
        print("Speed:           ");
        lcd_goto_xy(10,1);
        print_long(motorSpeed);
        
        // Print encoder errors, if there are any.
        if(encoders_check_error_m1())
        {
            lcd_goto_xy(0,1);
            print("Error 1");
        }
    }
}
