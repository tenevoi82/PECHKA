#include <Arduino.h>

class Led
{
private:
    int ledPin;       // Пин светодиода
    float brightness; // Текущая яркость
    float angle;      // Угол для синусоиды
    float speed;      // Скорость дыхания
    unsigned long last_update;

public:
    bool isActive; // Флаг активности

    Led(int pin, float fadeSpeed)
    {
        ledPin = pin;
        speed = fadeSpeed;
        brightness = 0;
        angle = 0;
        isActive = true;
        pinMode(ledPin, OUTPUT);
        last_update = millis();
    }

    void update()
    {
        if (millis() - last_update < 5)
            return;
        last_update = millis();

        brightness = (sin(angle) + 1) / 2 * 255; // Переводим синус в диапазон (0-255)
        int setbr= map((int)brightness, 0, 254, 0, 254);
        analogWrite(ledPin, setbr);
        if (!isActive && setbr == 254)
            return;
        else
        {
            angle += speed;
        }
        if (angle > 6.28)
            angle = 0; // Сброс угла (2π радиан = 360°)
    }
};