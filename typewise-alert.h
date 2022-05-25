#pragma once

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

BreachType checkBreachType(BatteryCharacter batteryChar, double temperatureInC)
void  alertTarget(AlertTarget alertTarget, BreachType breachType)
void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
void setLimits(CoolingType coolingType, int *upperLimit) 
void printControllerMessage(unsigned short header, BreachType breachType);
void printMessageTemp(const char* recepient, BreachType breachType);
