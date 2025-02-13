#include <Arduino.h>

class TempSensor
{
private:
    unsigned int last_update;
    bool last_state = false;
    uint8_t pin;

public:
    bool state = false;

    TempSensor(int pin)
    {
        this->pin = pin;
        pinMode(pin, INPUT);
        state = digitalRead(pin);
        last_update = millis();
    };

    bool update()
    {
        if(millis()-last_update < 20)
            return false;

        bool b = digitalRead(pin);
        if (b != state )
        {
            state = !state;
            return true;
        }
        else
            return false;
    };
};