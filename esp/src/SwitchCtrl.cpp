#include <Arduino.h>
int switchPin =  22;

void SwitchInit(){
    pinMode(switchPin, OUTPUT);
}

void SwitchCtrl(int status){
    if(status == 1){
        digitalWrite(switchPin, HIGH);  
    }else{
         digitalWrite(switchPin, LOW);  
    }
}