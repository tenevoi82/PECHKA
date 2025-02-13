#include <Arduino.h>

class Fan
{
private:
    int currentspeed;
    unsigned long lastupdate;
    int pin;
    int minSpeed;
    unsigned long timetooff;

public:
    Fan(uint8_t pin, int minSpeed)
    {
        this->pin = pin;
        this->minSpeed = minSpeed;
        pinMode(pin, OUTPUT);
        lastupdate = millis();
        analogWrite(pin, minSpeed);
        currentspeed = minSpeed;
    }

    void EnebleOnTime(int seconds)
    {
        timetooff = millis() + (seconds * 1000);
    }

    void update()
    {
        if (millis() - lastupdate < 4)
            return;
        lastupdate = millis();
        if (millis() > timetooff)
        {
            if (currentspeed > minSpeed)
            {
                currentspeed--;
            }
            analogWrite(pin, minSpeed);
            return;
        }
        if (currentspeed < 255)
        {
            currentspeed++;
            analogWrite(pin, currentspeed);
        }
    }
};
