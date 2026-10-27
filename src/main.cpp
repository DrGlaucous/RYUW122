#include <Arduino.h>
#include "SPI.h"
#include "dw3000.h"
#include "dw3000_regs.h"

DWUart* uart = nullptr;
DW3000Port* port = nullptr;
DW3000* radio = nullptr;
DummyStream* debugStream = nullptr;


void setup() {


    pinMode(PA2, OUTPUT);
    while(1)
    {
        digitalWrite(PA2, 1);
        delay(1000);
        digitalWrite(PA2, 0);
        delay(1000);
    }

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

    auto result = radio->dwt_check_dev_id();


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

