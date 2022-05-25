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

void setLimits(CoolingType coolingType, int *upperLimit) 
{
  if(coolingType == PASSIVE_COOLING) 
  {    
      return;
  }
  else if(coolingType == HI_ACTIVE_COOLING)      
  {    
      *upperLimit = 45;
  }
  else
  {
      *upperLimit = 40;
  } 

}

BreachType checkBreachType(BatteryCharacter batteryChar, double temperatureInC) {
  int lowerLimit = 0;
  int upperLimit = 35; 
  setLimits(batteryChar.coolingType, &upperLimit);
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

void printControllerMessage(unsigned short header, BreachType breachType)
{
    printf("%x : %x\n", header, breachType);
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printControllerMessage(header,breachType);
  
}

void printMessageTemp(const char* recepient, BreachType breachType)
{
    printf("To: %s\n", recepient);
    if(breachType == TOO_LOW)
    {
        printf("Hi, the temperature is too low\n");
        return ;
    }
    printf("Hi, the temperature is too high\n");
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  if(breachType == NORMAL)
  {
      return  ;
  }
  printMessageTemp(recepient, breachType);
    
}
