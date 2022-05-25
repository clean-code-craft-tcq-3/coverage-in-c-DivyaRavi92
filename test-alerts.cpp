#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(42, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
}

TEST_CASE("Alerts target based on breach type") {
  alertTarget(TO_CONTROLLER, TOO_LOW);
  alertTarget(TO_CONTROLLER, TOO_HIGH);
  alertTarget(TO_EMAIL, TOO_HIGH);
  alertTarget(TO_EMAIL, NORMAL);
}

TEST_CASE("Checks the breach type") {
  BatteryCharacter batteryChar = {PASSIVE_COOLING,{0}};
  REQUIRE(checkBreachType(batteryChar, 40) == TOO_HIGH);
}
