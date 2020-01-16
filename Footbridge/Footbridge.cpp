#include "Footbridge.h"


Footbridge::Footbridge(int pinGreen, int pinRed){
  green = pinGreen;
  red = pinRed;
  pinMode(green,  OUTPUT);
  pinMode(red,    OUTPUT);
}

/**
 * Displays the Green-Light
 */
void Footbridge::greenLight(){
  digitalWrite(red   , LOW);
  digitalWrite(green , HIGH);
}


/**
 * Displays the Red-Light
 */
void Footbridge::redLight(){
  digitalWrite(red   ,HIGH);
  digitalWrite(green , LOW);
}

/**
 * Displays no Light
 */
void Footbridge::noLight(){
  digitalWrite(red   , LOW);
  digitalWrite(green , LOW);
}