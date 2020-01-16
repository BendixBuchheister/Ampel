#include <trafficLight.h>
#include <Footbridge.h>

#define carGreen       (7)
#define carYellow      (9)
#define carRed         (11)
#define button         (5)
#define passGreen      (8)
#define passRed        (10)

/* Enum for defining the status of the traffic light */
enum Status {Status_Blinking, 
             Status_Change, 
             Status_Pause, 
             Status_Sleeping} 
     stat = Status_Blinking;
/* Enum which saves the current state of the TrafficLight */
enum {Light_Green, 
      Light_Yellow,
      Light_AllRedPG, 
      Light_Red, 
      Light_AllRedCG,
      Light_RedYellow, 
      Light_None} 
      light = Light_Red; 
  

/* Timer for activating Sleep Mode in ms */
const int SLEEPMODECD = 100000;
/* Duration the traffic Light stays on Yellow in ms*/
const int SWAPDURATION = 1000;
/* Duration the traffic Light stays on green/red in ms*/
const int STAYDURATION = 5000;
/* Duration one needs to push the button, to count as a long push in ms*/
const int LONGBUTTONPRESS = 300;
/* Status to save the old Status, while the traffic light is paused in ms */
Status temp;
uint32_t trafficLightTimer, //Timer to track traffic light durations
         sleepTimer,        //Timer to track sleep Mode
         buttonTimer;       //Timer to track long button pushes
boolean running = false;

/* Defining the trafficLight with the library for a traffic Light */
trafficLight ampel(carGreen,carYellow,carRed);

/* Defining the footbridge with the library for a footbridge */
Footbridge fussgaenger(passGreen,passRed);




void setup(){
  sleepTimer = setTimer(SLEEPMODECD);
  pinMode(button, INPUT_PULLUP);
}



void loop() {  
  /* Checking for Input */
  if (!digitalRead(button)){
    if (!running){
      /* Starting a timer to check how long the button is pressed */
      buttonTimer = setTimer(LONGBUTTONPRESS);
      running = true;
    }
  }else if (running && millis() >= buttonTimer){
    /* Button was detected as LONG push */
    switch (stat){
      case Status_Pause    : stat = temp;
                             break;
      case Status_Blinking : stat = Status_Change;
                             light = Light_Red;
                             break;
      case Status_Sleeping : 
      case Status_Change   : stat = Status_Blinking;
                             trafficLightTimer = setTimer(SWAPDURATION);
                             sleepTimer = setTimer(SLEEPMODECD);
                             break;
    }
    running = false;
  }else if (running){
    /* Button was detected as SHORT push */
    switch (stat){
      case Status_Pause    : stat = temp;
                             break;
      case Status_Blinking : stat = Status_Change;
                             light = Light_Red;
                             break;
      case Status_Sleeping : stat = Status_Blinking;
                             trafficLightTimer = setTimer(SWAPDURATION);
                             sleepTimer = setTimer(SLEEPMODECD);
                             break;
      case Status_Change   : temp = stat;
                             stat = Status_Pause;
    }
    running = false;
  } 
  
  /* Checking weather to go in sleepMode or stay awake */
  if (millis() >= sleepTimer && stat == Status_Blinking){
    stat = Status_Sleeping;
  }
  
  /*Checking the status, to decide what to do*/ 
  switch (stat){
    case Status_Blinking : blinking();
                           break;
    case Status_Change   : change();
                           break;
    case Status_Pause    : break;
    case Status_Sleeping : ampel.noLight();
                           fussgaenger.noLight();
                           light = Light_None;
  }
}



/**
 * TrafficLight blinks with Yellow Light
 */
void blinking(){
  if (millis() >= trafficLightTimer){
    switch (light){
      case Light_Yellow: ampel.yellowLight();
                         fussgaenger.redLight();
                         light = Light_None;
                         break;
      case Light_None  :
      default          : ampel.noLight();
                         fussgaenger.noLight();
                         light = Light_Yellow;
                         break;
    }
    trafficLightTimer = setTimer(SWAPDURATION);
  }
}



/**
 * TrafficLight runs from Red to Green, and back
 */
void change(){
  int offset = 0;
  if (millis() >= trafficLightTimer){
    switch (light) {
      case Light_Green    : ampel.greenLight();
                            fussgaenger.redLight();
                            offset = STAYDURATION;
                            light = Light_Yellow;
                            break;
      case Light_Yellow   : ampel.yellowLight();
                            fussgaenger.redLight();
                            offset = SWAPDURATION;
                            light = Light_AllRedPG;
                            break;
      case Light_AllRedPG : ampel.redLight();
                            fussgaenger.redLight();
                            offset = SWAPDURATION;
                            light = Light_Red;
                            break;
      case Light_AllRedCG : ampel.redLight();
                            fussgaenger.redLight();
                            offset = SWAPDURATION;
                            light = Light_RedYellow;
                            break;
      case Light_RedYellow: ampel.redYellowLight();
                            fussgaenger.redLight();
                            offset = SWAPDURATION;
                            light = Light_Green;
                            break;
      case Light_Red      :
      default             : ampel.redLight();
                            fussgaenger.greenLight();
                            offset = STAYDURATION;
                            light = Light_AllRedCG;
                            break;
    }   
    trafficLightTimer = setTimer(offset);
  }
}

/**
 * Sets the given Timer offset ms higher than millis()
 * @timer Timer which is being reseted
 * @offest offset for the timer
 */
uint32_t setTimer (int offset){
  return millis() + offset;
}
