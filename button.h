////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//////
////// Simple classes by Ziotester Lab
//////
////// Info, guides and tutorials on:
////// https://ziotester.github.io
//////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
#include <Arduino.h>

class Button {
  private:
    int pin;
    long lastDebounceTime = 0; 
    long debounceDelay = 100; 
    int lastSteadyState = HIGH;  
    int lastFlickerableState = HIGH; 
    int state = HIGH;

  public:

    void init(int pin) {
      this->pin = pin;
      pinMode(this->pin, INPUT_PULLUP);
      digitalWrite(this->pin, LOW);
    } 

    /*

    return true every state changed (press and release)

    */
    boolean changed() {
      this->state = digitalRead(this->pin);

      if (this->state != this->lastFlickerableState) {
        this->lastDebounceTime = millis();
        this->lastFlickerableState = this->state;
      }

      if ((millis() - this->lastDebounceTime) > this->debounceDelay) {
        if(this->lastSteadyState != this->state){
          this->lastSteadyState = this->state;
          return true;          
        } else {
          return false;
        }
      } else {
        return false;
      }
    }

    /*

    return true at press only

    */
    boolean clicked() {
      this->state = digitalRead(this->pin);

      if (this->state != this->lastFlickerableState) {
        this->lastDebounceTime = millis();
        this->lastFlickerableState = this->state;
      }

      if ((millis() - this->lastDebounceTime) > this->debounceDelay) {
        if(this->lastSteadyState != this->state){
          this->lastSteadyState = this->state;
          if(!this->state){
            return true;    
          } else {
            return false;
          }     
        } else {
          return false;
        }
      } else {
        return false;
      }
    }
};