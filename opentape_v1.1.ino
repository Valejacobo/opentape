#include "libraries/SevSeg.h"
SevSeg sevseg;
//SevSeg.h is the library used to drive numbers into seven segments displays

//Input pins definition, trigger and echo from ultrasonic sensor
#define trigPin 2
#define echoPin 3

//Inputs from encoder wheel and button 
#define inputA 4
#define inputB 5
#define button 6

//Variables definition
long duration;
int offset = 0;
int distance;
int mode = 0;
int aState;
int aLastState;
int bState;

//Display Setup, number of display digits, pins used to output signal to it and various display settings
byte numDigits = 4;
byte digitPins[] = {7, 8, 9, 10};
byte segmentPins[] = { A0, A1, A2, A3, A4, A5, A6, A7 };
bool resistorsOnSegments = true;
byte hardwareConfig = COMMON_CATHODE;
sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
sevseg.setBrightness(100);

//Pins setup and initialization of pins, serial and encoder wheel button
pinMode (trigPin, OUTPUT);
pinMode (echoPin, INPUT);
pinMode (inputA, INPUT);
pinMode (inputB, INPUT);
pinMode(button, INPUT);

Serial.begin (9600);
aLastState = digitalRead(inputA);

//Main loop, switches between the two working modes, switches on encoder button press
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

//Calibration function, sets distance from camera sensor plane to ultrasonic sensor
void calibration(){
    sevseg.setNumber(offset);
    sevseg.refreshDisplay();
	
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

//Main working mode, measures distance from ultrasonic sensor to subject
void tape(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    distance = ((duration / 2) + offset) / 29.1;

    sevseg.setNumber(distance);
    sevseg.refreshDisplay();
}