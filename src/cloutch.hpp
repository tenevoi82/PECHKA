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
    int openingtime;

    bool openAtButton = false;
    bool openattimer = false;


    void OpenOnTimer(int Seconds){
        openattimer = true;
        timeToClose = millis() + Seconds*1000;
    }

public:
    Cloutch(uint8_t pin, int timerSecons, int openingtime) {
        this->pin = pin;        
        this->timerSecons = timerSecons;
        this->openingtime = openingtime;
        pinMode(pin,OUTPUT);
    };


    void OpenOnTime(int Seconds){
        openattimer = false;
        openAtButton = true;
        timeToClose = millis() + Seconds*1000;
        currentState = true;
        digitalWrite(pin,currentState);
    }
    
    void update(){
        if(openAtButton && millis() > timeToClose){ 
            openAtButton =false;
            currentState = false;
            digitalWrite(pin,currentState);
            lastClose = millis();
            return;
        }
        if(openattimer && millis() > timeToClose){
            openattimer = false;
            currentState = false;
            digitalWrite(pin,currentState);
            lastClose = millis();
            return;
        }
        
        if(!openAtButton && !openattimer && (millis() > lastClose + timerSecons*1000)){
            timeToClose = millis() + openingtime*1000;
            openattimer = true;
            currentState = true;
            digitalWrite(pin,currentState);
        }
    }
};
