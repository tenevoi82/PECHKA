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


    /* data */
public:
    Cloutch(uint8_t pin, int timerSecons, int openingtime) {
        this->pin = pin;        
        this->timerSecons = timerSecons;
        this->openingtime = openingtime;
        pinMode(pin,OUTPUT);

    };


    void OpenOnTime(int Seconds){
        // Serial.println("4");
        openattimer = false;
        openAtButton = true;
        timeToClose = millis() + Seconds*1000;
        currentState = true;
        digitalWrite(pin,currentState);
    }
    
    void update(){
        // Serial.println("U");
        //delay(1000);
        if(openAtButton && millis() > timeToClose){ 
            // Serial.println("1");
            openAtButton =false;
            currentState = false;
            digitalWrite(pin,currentState);
            lastClose = millis();
            return;
        }
        if(openattimer && millis() > timeToClose){
            // Serial.print("2 -> ");
            // Serial.print("openattimer = ");
            // Serial.print(openattimer);
            // Serial.print(", timeToClose = ");
            // Serial.print(timeToClose);
            // Serial.print(", millis = ");
            // Serial.println(millis());
            openattimer = false;
            currentState = false;
            digitalWrite(pin,currentState);
            lastClose = millis();
            return;
        }
        
        if(!openAtButton && !openattimer && (millis() > lastClose + timerSecons*1000)){
            // Serial.print("3 -> ");
            timeToClose = millis() + openingtime*1000;
            // Serial.print("Set timeToClose = "); 
            // Serial.println(millis() + openingtime*1000);
            openattimer = true;
            currentState = true;
            digitalWrite(pin,currentState);
        }
        // Serial.print("N -> ");
        // Serial.print("openAtButton = ");
        // Serial.print(openAtButton);
        // Serial.print(", openattimer = ");
        // Serial.print(openattimer);
        // Serial.print(", lastClose = ");
        // Serial.print(lastClose);
        // Serial.print(", timerSecons = ");
        // Serial.print(timerSecons);
        // Serial.print(", millis = ");
        // Serial.println(millis());

    }
};
