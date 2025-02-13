#include <Arduino.h>

// outputs
#define PIN_LED 11
#define PIN_FAN 10
#define PIN_CLOUTCH 12

// inputs
#define PIN_TEMP_OK A1
#define PIN_FOTO_SENS A2
#define PIN_BUTTON A3

#include "led.hpp"
#include "tempsensor.hpp"
#include "fan.cpp"
#include "cloutch.hpp"
#include "contact.hpp"

#define MINFAN 35          // Минимальная скорость вращения венитилятра
#define TIMETOENABLEFAN 15 // Время в секундах работы вентилятора на максимальных оборотах после обнаружения руки

#define FADE_SPEED 0.05 // Скорость дыхания светодиодной подсветки

Led led(PIN_LED, FADE_SPEED); // Создаем объект для управления светодиодом
Fan fan(PIN_FAN, MINFAN);
Cloutch cloutch(PIN_CLOUTCH, 60, 2);

Contact fotoSensor(PIN_FOTO_SENS, 300);
Contact btn(PIN_BUTTON, 200);
Contact tempOk(PIN_TEMP_OK);

void pinsettings()
{
    // Пины D9 и D10 - 31.4 кГц
    TCCR1A = 0b00000001; // 8bit
    TCCR1B = 0b00000001; // x1 phase correct
}

void setup()
{
    // pinsettings();
    Serial.begin(115200);
}

void loop()
{
    if (!fotoSensor.getState())
        fan.EnebleOnTime(TIMETOENABLEFAN);
    if (!btn.getState())
        cloutch.OpenOnTime(10);
    led.isActive = tempOk.getState();

    cloutch.update();
    fan.update();
    led.update();
}
