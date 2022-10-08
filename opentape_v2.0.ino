#include "TFMini.h"
#include <Wire.h>
#include "SSD1306Wire.h"

//Global variables used by the functions.
#define inputA 4
#define inputB 5
#define button 6

int offset = 0;
uint16_t distance;
uint16_t strength;
int mode = 0;
int aState;
int aLastState;
int bState;

pinMode (inputA, INPUT);
pinMode (inputB, INPUT);
pinMode(button, INPUT);

//Parameters setup and init.
void setup(){

    
    Serial.begin(115200);
    Serial1.begin(TFMINI_BAUDRATE);
    tfmini.begin(&Serial1);
    delay(100);
    tfmini.setSingleScanMode();

    SSD1306Wire display(0x3c, SDA, SCL);
    display.init();
    display.setFont(ArialMT_Plain_10);
}

//Mode switching main loop;
void loop() {
 
    bState = digitalRead(button);
    if (bState == HIGH && mode == 0) {
        mode = 1;
    }
    else if (bstate == HIGH && mode == 1) {
        mode = 0;
    }
    else {
        if (mode == 0) {
            tape();
        }
        else {
            calibration();
        }
    }
}

//Offset calibration mode
void calibration(){

    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ARIALMT_Plain_10);
    display.drawString(0,0,"Offset: ");
    display.drawString(0,10,)
    aState = digitalRead(inputA);
    if (aState != aLastState) {
        if (digitalRead(inputB) != aState) {
            offset++;
        }
        else {
            offset--;
        }
    }
}
