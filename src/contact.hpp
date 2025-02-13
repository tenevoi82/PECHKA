#include <Arduino.h>
class Contact
{
private:
    int pin;                        // Пин, к которому подключена кнопка
    bool lastState;                 // Предыдущее состояние кнопки
    unsigned long lastDebounceTime; // Время последнего изменения состояния
    unsigned long debounceDelay;    // Задержка для устранения дребезга

public:
    bool currentState; // Текущее состояние кнопки
    // Конструктор класса Button
    // buttonPin - пин кнопки
    // debounceTime - время подавления дребезга (по умолчанию 50 мс)
    Contact(int buttonPin, unsigned long debounceTime = 50)
    {
        pin = buttonPin;
        debounceDelay = debounceTime;
        pinMode(pin, INPUT); // Устанавливаем режим подтягивающего резистора
        lastState = HIGH;    // Начальное состояние кнопки (отпущена)
        currentState = HIGH;
        lastDebounceTime = 0;
    }

    bool update()
    {
        bool reading = digitalRead(pin);
        if (reading != lastState)
        {
            lastDebounceTime = millis();
            lastState = reading;
        }
        if (lastDebounceTime + debounceDelay < millis())
        {
            currentState = reading;
            return true;
        }else return false;
    }
    bool getState()
    {
        update();
        return currentState;
    }
};