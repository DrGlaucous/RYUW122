#include <Arduino.h>
#include "SPI.h"
#include "dw3000.h"
#include "dw3000_regs.h"

DWUart* uart = nullptr;
DW3000Port* port = nullptr;
DW3000* radio = nullptr;
DummyStream* debugStream = nullptr;


void setup() {

    //brute-force: set all compatible pins to INPUT mode and check for voltage levels
    int searchPins[] = {
        //PA13, //SWDIO
        PA15,
        PB4,
        PB7,
        PA12, //pulled low
        //PA14, //SWCLK
        PB3, //pulled low
        PB6, //5
        PB8,
        PA10, //RXD
        PA11,
        PB1, //9 pulled low
        PB5,
        PA9, //TXD
        PB11, //12 pulled low
        PB0,
        PA0,
        PA8,
        PB10, //16 pulled low
        PA6, //17 pulled low
        PA4,
        PA2,
        PB2,
        PA7,
        PA5,
        PA3,
        PA1
    };

    //high pins: //3,4,9,12,16,17
    bool expectedValues[] = {
        true, //0
        true,
        true,
        false, //3
        false, //4
        true,
        true,
        true,
        true,
        false, //9

        true,
        true,
        false, //12
        true,
        true,
        true,
        false, //16
        false, //17
        true,
        true,

        true,
        true,
        true,
        true,
        true,
        true,
        true,

    };

    //int searchPinCount = 27;
    int searchPinCount = sizeof(searchPins) / sizeof(int);
    for(int i = 0; i < searchPinCount; ++i)
    {
        pinMode(searchPins[i], INPUT_PULLUP);
    }
    while(1)
    {
        for(int i = 0; i < searchPinCount; ++i)
        {
            if(digitalRead(searchPins[i]) == expectedValues[i]) {
                //pin is high
                int apple3 = digitalRead(searchPins[i]);
            }
            else {
                //pin is different, something's afoot (we should set a breakpoint here)
                int apple3 = digitalRead(searchPins[i]);
            }

        }
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

