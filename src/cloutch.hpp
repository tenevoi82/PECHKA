#include <Arduino.h>

class Cloutch
{
private:
    bool currentState;
    unsigned long lastupdate;
    int pin;
    unsigned long lastClose;
    unsigned long timeToClose;
    unsigned long timerSecons;
    unsigned long  openingtime;

    bool openAtButton = false;
    bool openattimer = false;


    void OpenOnTimer(unsigned long Seconds){
        openattimer = true;
        timeToClose = millis() + Seconds*1000;
    }

public:
    Cloutch(uint8_t pin, unsigned long timerSecons, unsigned long openingtime) {
        this->pin = pin;        
        this->timerSecons = timerSecons;
        this->openingtime = openingtime;
        pinMode(pin,OUTPUT);
    };


    void OpenOnTime(unsigned long Seconds){
        openattimer = false;
        openAtButton = true;
        timeToClose = millis() + Seconds*1000;
        currentState = true;
        digitalWrite(pin,currentState);
        Serial.println("открываю от кнопки");
        Serial.print("Сейчас ");Serial.print(millis()); Serial.print("ms, Закрою в ");Serial.println(timeToClose); Serial.println("ms");
    }
    
    void update(){
        if(openAtButton && millis() > timeToClose){ //если открыт от кнопки и время уже закрывать
            Serial.println("открыт от кнопки и время уже закрывать");
            openAtButton =false;
            currentState = false;
            digitalWrite(pin,currentState);
            lastClose = millis();
            return;
        }
        if(openattimer && millis() > timeToClose){ // если открыт по таймеру и время закрывать
            Serial.println("открыт по таймеру и время закрывать");
            openattimer = false;
            currentState = false;
            digitalWrite(pin,currentState);
            lastClose = millis();
            return;
        }
        
        if(!openAtButton && !openattimer && (millis() > lastClose + timerSecons*1000)){     //если не работает по кнопке и таймеру и
                                                                                            //пришло время открывть
            Serial.println("не работает по кнопке и таймеру и пришло время открывть");                                                                              
            timeToClose = millis() + openingtime*1000;
            openattimer = true;
            currentState = true;
            digitalWrite(pin,currentState);
        }
    }
};
