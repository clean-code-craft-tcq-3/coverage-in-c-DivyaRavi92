#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

void setLimits(CoolingType coolingType, int *lowerLimit, int *upperLimit) 
{
  switch(coolingType) {
    case PASSIVE_COOLING:
      *lowerLimit = 0;
      *upperLimit = 35;
      break;
    case HI_ACTIVE_COOLING:
      *lowerLimit = 0;
      *upperLimit = 45;
      break;
    case MED_ACTIVE_COOLING:
      *lowerLimit = 0;
      *upperLimit = 40;
      break;
  }
}

void checkBreachType(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
  int lowerLimit = 0;
  int upperLimit = 0; 
  setLimits(batteryChar.coolingType, &lowerLimit, &upperLimit);
  BreachType breachType = inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void  alertTarget(AlertTarget alertTarget, BreachType breachType)
{
  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

printControllerMessage(unsigned short header, BreachType breachType)
{
    printf("%x : %x\n", header, breachType);
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printControllerMessage(header,breachType);
  
}

printMessageLowTemp(char* recepient)
{
    printf("To: %s\n", recepient);
    printf("Hi, the temperature is too low\n");
}

printMessageHighTemp(char* recepient)
{
    printf("To: %s\n", recepient);
    printf("Hi, the temperature is too high\n");
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  switch(breachType) {
    case TOO_LOW:
     printMessageLowTemp(recepient);
      break;
    case TOO_HIGH:
      printMessageHighTemp(recepient);
      break;
    case NORMAL:
      break;
  }
}
