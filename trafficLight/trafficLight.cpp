#include "trafficLight.h"


trafficLight::trafficLight(int pinGreen, int pinYellow, int pinRed){
  green = pinGreen;
  yellow = pinYellow;
  red = pinRed;
  pinMode(green,  OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red,    OUTPUT);
}

/**
 * Displays the Green-Light
 */
void trafficLight::greenLight(){
  digitalWrite(red   , LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green , HIGH);
}

/**
 * Displays the Yellow-Light
 */
void trafficLight::yellowLight(){
  digitalWrite(red   , LOW);
  digitalWrite(yellow,HIGH);
  digitalWrite(green , LOW);
}

/**
 * Displays the Red-Light
 */
void trafficLight::redLight(){
  digitalWrite(red   ,HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(green , LOW);
}

/**
 * Displays Red- and Yellow-Light
 */
void trafficLight::redYellowLight(){
  digitalWrite(red   ,HIGH);
  digitalWrite(yellow,HIGH);
  digitalWrite(green , LOW);
}

/**
 * Displays no Light
 */
void trafficLight::noLight(){
  digitalWrite(red   , LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green , LOW);
}