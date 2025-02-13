#include <Arduino.h>

#include "../include/settings.hpp"
#include "settings.hpp"

#define MINFAN 35
#define MAXFAN 255

void pinsettings() {
    pinMode(PIN_TEMP_OK, INPUT);
    pinMode(PIN_BUTTON, INPUT);
    pinMode(PIN_FOTO_SENS, INPUT);

    pinMode(PIN_FAN, OUTPUT);
    pinMode(PIN_CLOUTCH, OUTPUT);
    pinMode(PIN_LED, OUTPUT);

    // // Пины D9 и D10 - 4 кГц
    // TCCR1A = 0b00000001;  // 8bit
    // TCCR1B = 0b00000010;  // x8 phase correct

    // Пины D9 и D10 - 31.4 кГц
    TCCR1A = 0b00000001;  // 8bit
    TCCR1B = 0b00000001;  // x1 phase correct
}

void setup() {
    pinsettings();
    Serial.begin(9600);

    Serial.println("Максимальная яркость на 3 секунд");
    analogWrite(PIN_LED, 255);
    // while(true){};
    delay(1 * 1000);

    Serial.println("Минимальная яркость на 3 секунд");
    analogWrite(PIN_LED, 0);
    delay(1 * 1000);

    Serial.println("Тест двигателя:");
    for (int i = MINFAN; i < 255; i++) {
        // Serial.print("Запуск двигателя на ");
        // Serial.print(map(i, MINFAN, MAXFAN, 0, 100));
        // Serial.print("%");
        // Serial.print(" = ");
        // Serial.println(i);
        analogWrite(PIN_FAN, i);
        delayMicroseconds(2500);
    }
    delay(5000);
    analogWrite(PIN_FAN, MINFAN);
}

unsigned long timer[10];
int brightness = 0;
int s = 1;

enum clutchState { open = false,
                   close = true };
clutchState d = open;

void Clutch(clutchState j) {
    digitalWrite(PIN_CLOUTCH, j);
    Serial.println(j);
    d = j;
}

bool sensor = false;
void loop() {
    if (digitalRead(PIN_FOTO_SENS) != sensor) {
        sensor = !sensor;
        Serial.println(sensor ? "Нет руки" : "Есть рука");
        if (!sensor) {
            analogWrite(PIN_FAN, MAXFAN);
            delay(4 * 1000);
            analogWrite(PIN_FAN, MINFAN);
        }
    }

    if (millis() - timer[0] > 5) {
        timer[0] = millis();
        if (brightness == 255) {
            s = -1;
        }
        if (brightness == 30) {
            s = 1;
        }
        brightness += s;
        analogWrite(PIN_LED, brightness);
    }
    if (millis() - timer[1] > 10000) {
        timer[1] = millis();
        if (d == open) {
            Serial.println("Закрываю задвижку.");
            Clutch(close);
        } else {
            Serial.println("Открываю задвижку.");
            Clutch(open);
        }
    }
}
