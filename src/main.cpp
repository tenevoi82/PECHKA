#include <Arduino.h>

//outputs
#define PIN_LED 11
#define PIN_FAN 10
#define PIN_CLOUTCH 12

//inputs
#define PIN_TEMP_OK A1
#define PIN_FOTO_SENS A2
#define PIN_BUTTON A3

#include "led.hpp"
#include"tempsensor.hpp"
#include"fan.cpp"
#include "cloutch.hpp"


#define MINFAN 35
#define TIMETOENABLEFAN 15

#define FADE_SPEED 0.05 // Скорость дыхания
BreathingLED led(PIN_LED, FADE_SPEED); // Создаем объект для управления светодиодом
TempSensor temp(PIN_TEMP_OK);
Fan fan(PIN_FAN,MINFAN);
Cloutch cloutch(PIN_CLOUTCH,60,2);



void pinsettings() {
    pinMode(PIN_TEMP_OK, INPUT);
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_FOTO_SENS, INPUT);

    // // Пины D9 и D10 - 4 кГц
    // TCCR1A = 0b00000001;  // 8bit
    // TCCR1B = 0b00000010;  // x8 phase correct

    // Пины D9 и D10 - 31.4 кГц
    TCCR1A = 0b00000001;  // 8bit
    TCCR1B = 0b00000001;  // x1 phase correct
}

void setup() {
    pinsettings();
    Serial.begin(115200);
}



void loop() {

    if(!digitalRead(PIN_FOTO_SENS)){
        fan.EnebleOnTime(TIMETOENABLEFAN);
    }
    if(!digitalRead(PIN_BUTTON)){
        cloutch.OpenOnTime(10);
    }
    cloutch.update();
    fan.update();
    led.update();
    if(temp.update()){
        led.isActive = temp.state;
    }
}
