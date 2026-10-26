#include <Arduino.h>
#include "SPI.h"
#include "dw3000.h"
#include "dw3000_regs.h"

DWUart* uart = nullptr;
DW3000Port* port = nullptr;
DW3000* radio = nullptr;


//spi chip select is pin 37
//hardware reset is pin 33
//spi interrupt is pin 1

#define SPI_CS 32 + 6
#define DW_RST 25
#define DW_IRQ 32 + 2


void setup() {

    SPI.begin();

    pinMode(PA0, OUTPUT);

	//uart = new DWUart(115200);
	//port = new DW3000Port(&SPI, SPI_CS, DW_RST, DW_IRQ);
	//radio = new DW3000(uart, port);



    delay(1000);


}


uint32_t wowzers = 0;
void loop() {

    delay(1000);
    wowzers += 1;
    delay(1000);
    wowzers += 1;

}

