#include <Arduino.h>

// outputs
#define PIN_LED 11
#define PIN_FAN 10
#define PIN_CLOUTCH 12

// inputs
#define PIN_TEMP_OK A1
#define PIN_FOTO_SENS A2
#define PIN_BUTTON A3

#include "cloutch.hpp"
#include "contact.hpp"
#include "fan.cpp"
#include "led.hpp"
#include "tempsensor.hpp"

#define MINFAN 40          // Минимальная скорость вращения венитилятра
#define TIMETOENABLEFAN 1  // Время в секундах работы вентилятора на максимальных оборотах после обнаружения руки

#define FADE_SPEED 0.007  // Скорость дыхания светодиодной подсветки

Led led(PIN_LED, FADE_SPEED);  // Создаем объект для управления светодиодом
Fan fan(PIN_FAN, MINFAN);
Cloutch cloutch(PIN_CLOUTCH, 45 * 60, 2 * 60);

Contact fotoSensor(PIN_FOTO_SENS, 50);
Contact btn(PIN_BUTTON);
Contact tempOk(PIN_TEMP_OK);

void pinsettings() {
    // Пины D9 и D10 - 31.4 кГц
    TCCR1A = 0b00000001;  // 8bit
    TCCR1B = 0b00000001;  // x1 phase correct
}

void setup() {
    pinsettings();
    Serial.begin(115200);
    Serial.println("RESTART");
}

void loop() {
    if (!fotoSensor.getState())
        fan.EnebleOnTime(TIMETOENABLEFAN);
    if (!btn.getState())
        cloutch.OpenOnTime(1800);
    if (tempOk.getState()) {
        led.isActive = true;
    }else{
        led.isActive = false;
    }

    cloutch.update();
    fan.update();
    led.update();
}
