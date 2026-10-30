#include <Arduino.h>
#include "SPI.h"
#include "dw3000.h"
#include "dw3000_regs.h"
#include <string>

DWUart* uart = nullptr;
DW3000Port* port = nullptr;
DW3000* radio = nullptr;
DummyStream* debugStream = nullptr;


void setup() {

    //brute-force: set all compatible pins to INPUT mode and check for voltage levels
    int searchPins[] = {
        //PA13, //SWDIO IDENTIFIED
        PA15,
        PB4,
        PB7, //IDENTIFIED
        PA12, //pulled low
        //PA14, //SWCLK IDENTIFIED
        PB3, //connected to pin 34 (SPICLK) on the DW3000 verified
        PB6, //5 IDENTIFIED
        PB8,
        PA10, //RXD IDENTIFIED
        PA11,
        PB1, //9 pulled low (wired to DW3000 WAKEUP 32 verified)
        PB5, //connected to pin 31 (EXTON) on the DW3000 verified, weird 1.5 volts when asserted by the STM32 though...
        PA9, //TXD IDENTIFIED
        PB11, //12 pulled low
        PB0,
        PA0, //14
        PA8, //15 pin 33 (RSTn) on the DW3000 verified
        PB10, //16 pulled low
        PA6, //17 pulled low (wired to DW3000 IRQ 1)
        PA4, //18
        PA2, //19 IDENTIFIED
        PB2, //20
        PA7, //21 IDENTIFIED
        PA5, //22 IDENTIFIED
        PA3, //23 IDENTIFIED
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

    std::string searchPinsName[] = {
        "PA15",
        "PB4",
        "PB7", 
        "PA12",
        "PB3", 
        "PB6",
        "PB8",
        "PA10",
        "PA11",
        "PB1",
        "PB5",
        "PA9",
        "PB11",
        "PB0",
        "PA0", 
        "PA8", 
        "PB10",
        "PA6", 
        "PA4", 
        "PA2", 
        "PB2", 
        "PA7", 
        "PA5", 
        "PA3", 
        "PA1"
    };

    
    //int searchPinCount = 27;
    int searchPinCount = sizeof(searchPins) / sizeof(int);

    //pulls pins up and breaks if their values change
    if(0){
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

    }

    if(0){
        //"blinks" the pins
        for(int i = 0; i < searchPinCount; ++i)
        {
            //re-using this, stores the states of the pins
            expectedValues[i] = false;
            pinMode(searchPins[i], OUTPUT);
        }
        int lastCurrentTime = millis();
        while(1)
        {
            //only run the code below once per millisecond change
            int currentTime = millis();
            if(currentTime == lastCurrentTime) {
                continue;
            }
            lastCurrentTime = currentTime;


            for(int i = 0; i < searchPinCount; ++i)
            {
                //adding 1 to i so that we don't divide by 0
                if(currentTime % (i + 1) == 0)
                {
                    expectedValues[i] = !expectedValues[i];
                    digitalWrite(searchPins[i], expectedValues[i]);
                }
            }

        }

    }

    if(0){
        for(int i = 0; i < searchPinCount; ++i)
        {
            pinMode(searchPins[i], OUTPUT);
        }

        while(1) {
            for(int j = 0; j < searchPinCount; ++j)
            {
                digitalWrite(searchPins[j], 1);
            }
            delay(1000);
            for(int j = 0; j < searchPinCount; ++j)
            {
                digitalWrite(searchPins[j], 0);
            }
            delay(2000);
        }
    }

    if(1){
        for(int i = 0; i < searchPinCount; ++i)
        {
            pinMode(searchPins[i], OUTPUT);
        }

        while(1) {

            for(int i = 0; i < searchPinCount; ++i)
            {
                //reset all pins
                for(int j = 0; j < searchPinCount; ++j)
                {
                    digitalWrite(searchPins[j], 0);
                }

                delay(100);

                
                //set the pin of interest
                digitalWrite(searchPins[i], 1);

                //random thing that can't be optimized out
                int apple = i * searchPins[i] + millis();

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

