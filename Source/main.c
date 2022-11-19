/* LEDs
0 : LED red     (PD14)
1 : LED blue 	(PD15)
2 : LED orange  (PD13)
3 : LED green	(PD12)
*/

#include "stm32f4xx.h"

// Number of LEDs
#define NUMBER_OF_LEDS 4

/* Functions */
int main(void);
void delay(uint32_t);
void init_leds();
void turn_name_on();
void turn_surname_on();
void turn_name_off();
void turn_surname_off();

// Enum for LEDs 
enum leds{red = 14, blue = 15, orange = 13, green = 12};
char firstName[4] = {'E','m','r','e'};
char surName[6] = {'O','z','t','u','r','k'};
uint32_t delayFactor = 10000000;


static uint32_t ledPin = 0;

uint32_t ledSelectFirstName = 0;

uint32_t ledSelectSurname = 0;

uint16_t numberOfBlinksName = 0;

uint16_t numberOfBlinksSurname = 0;

int main(void)
{
		// Enable the GPIOD port clock and  LED pins  output 
		init_leds();

		// turn on the LED first name
		turn_name_on();
		delay(delayFactor);
		// Turn off the LED  first name
		turn_name_off();
		delay(delayFactor);

		// turn on the LED blinks surname
		turn_surname_on();
		delay(delayFactor);
		// Turn off the LED for surname
		turn_surname_off();
}

void init_leds()
{
	// Enable the clock of port D of the GPIO
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	// Set LED pins in G P O Mode
	GPIOD->MODER &= 0x00000000;
	GPIOD->MODER |= (0x01 << 2*12 | 0x01 << 2*13 | 0x01 << 2*14 | 0x01 << 2*15);

	// Set LED pins as pull-up
    GPIOD->PUPDR &= 0x00000000;
    GPIOD->PUPDR |= (0x01 << 2*12 | 0x01 << 2*13 | 0x01 << 2*14 | 0x01 << 2*15);
}

void turn_name_on()
{
	// Stores the number of LED blinks 
	uint8_t blinkCounter = 0;
	// Number of blinks required for first name
	numberOfBlinksName = sizeof(firstName);

	// Calculating the ASCII sum of first name letters
	for(uint16_t i = 0; i < sizeof(firstName); i++)
		ledSelectFirstName += firstName[i];

	ledSelectFirstName %= NUMBER_OF_LEDS;

	// Select the correct LED based on the result
	if(ledSelectFirstName == 0)
		ledPin = red;
	else if(ledSelectFirstName == 1)
		ledPin = blue;
	else if(ledSelectFirstName == 2)
		ledPin = orange;
	else if(ledSelectFirstName == 3)
		ledPin = green;

	// turn on LED blinks
	while(1)
	{
	    // Set ledPin High
	    GPIOD->ODR |= (1 << ledPin);
	    delay(delayFactor);
	    // Toggle ledPin
        GPIOD->ODR ^= (1 << ledPin);
        delay(delayFactor);

        blinkCounter++;

        if(blinkCounter == numberOfBlinksName)
        	break;
	}
}

void turn_surname_on()
{
	uint8_t blinkCounter = 0;
	// Number of blinks required for surname
	numberOfBlinksSurname = sizeof(surName);

	// Calculates the ASCII sum of surname characters
	for(uint16_t i = 0; i < sizeof(surName); i++)
		ledSelectSurname += surName[i];

	ledSelectSurname %= NUMBER_OF_LEDS;

	if(ledSelectSurname == 0)
		ledPin = red;
	else if(ledSelectSurname == 1)
		ledPin = blue;
	else if(ledSelectSurname == 2)
		ledPin = orange;
	else if(ledSelectSurname == 3)
		ledPin = green;

	while(1)
	{
	    GPIOD->ODR |= (1 << ledPin);
	    delay(delayFactor);
        GPIOD->ODR ^= (1 << ledPin);
        delay(delayFactor);

        blinkCounter++;

        if(blinkCounter == numberOfBlinksSurname)
        	break;
	}
}

void turn_name_off()
{
	// Turn off the last ledpin
	GPIOD->ODR &= (0 << ledPin);
}

void turn_surname_off()
{
	// Turn off the last ledPin
	GPIOD->ODR &= (0 << ledPin);
}

void delay(uint32_t s)
{
		// Function for delay
        for(s; s>0; s--){
                asm("NOP");
        }
}
