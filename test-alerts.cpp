#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewiseAlert.h"
#include "stdbool.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(42, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
}

TEST_CASE("Alerts target based on breach type") {
  REQUIRE(alertTarget(TO_CONTROLLER, TOO_LOW) == 1);
  REQUIRE(alertTarget(TO_CONTROLLER, TOO_HIGH) == 1);
  REQUIRE(alertTarget(TO_EMAIL, TOO_HIGH) == 2);
  REQUIRE(alertTarget(TO_EMAIL, TOO_LOW) == 2);
  REQUIRE(alertTarget(TO_EMAIL, NORMAL) == 2);
}

TEST_CASE("Checks the breach type PASSIVE_COOLING") {
  BatteryCharacter batteryChar = {PASSIVE_COOLING,{0}};
  REQUIRE(checkBreachType(batteryChar, 40) == TOO_HIGH);
}  
TEST_CASE("Checks the breach type HI_ACTIVE_COOLING") {
  BatteryCharacter batteryChar = {HI_ACTIVE_COOLING,{0}};
  REQUIRE(checkBreachType(batteryChar, 40) == NORMAL);
}  
TEST_CASE("Checks the breach type MED_ACTIVE_COOLING") {
  BatteryCharacter batteryChar = {MED_ACTIVE_COOLING,{0}};
  REQUIRE(checkBreachType(batteryChar, -2) == TOO_LOW);
}
