#include <Arduino.h>
#include "SPI.h"
#include "dw3000.h"
#include "dw3000_regs.h"

DWUart* uart = nullptr;
DW3000Port* port = nullptr;
DW3000* radio = nullptr;
DummyStream* debugStream = nullptr;


#define PA0                     0
#define PA1                     1
#define PA2                     2
#define PA3                     3
#define PA4                     4
#define PA5                     5
#define PA6                     6
#define PA7                     7
#define PA8                     8
#define PA9                     9
#define PA10                    10
#define PA11                    11
#define PA12                    12
#define PA13                    13
#define PA14                    14
#define PA15                    15
#define PB0                     16
#define PB1                     17
#define PB2                     18
#define PB3                     19
#define PB4                     20
#define PB5                     21
#define PB6                     22
#define PB7                     23
#define PB8                     24
#define PB9                     25
#define PB10                    26
#define PB11                    27
#define PB12                    28
#define PB13                    29
#define PB14                    30
#define PB15                    31
#define PC13                    32
#define PC14                    33
#define PC15                    34
#define PH0                     35
#define PH1                     36


void setup() {

    SPI.setSCLK(PB3);
    SPI.setMISO(PA11);
    SPI.setMOSI(PA12);
    SPI.setSSEL(PA4);
    SPI.begin();

    //pinMode(PA0, OUTPUT);

	debugStream = new DummyStream();
	uart = new DWUart(*debugStream);
    port = new DW3000Port(&SPI, PA4, PA7, PB8);
	radio = new DW3000(uart, port);


    port->reset();
	
	if (radio->dwt_initialise(0) == DWT_ERROR)
	{
		while (1)
		{
			//error
			delay(1000);
		};
	}


	radio->gpio_init_output();


    delay(1000);




}


uint32_t wowzers = 0;
void loop() {

    delay(1000);
    wowzers += 1;
    delay(1000);
    wowzers += 1;

}

