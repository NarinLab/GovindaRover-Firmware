/*
 * GRM3 - Govinda Rover Mark III Firmware
 * Model: ATMega328P Microcontroller Unit (Arduino Nano)
 * License: AGPLv3
 * Researched & Maintained by PRITA & NarinLab, 2021
 * prita.undiknas.ac.id | narin.co.id | tutorkeren.com
 */

#include <Arduino.h>
#include "GRM3.h"

GRM3 govinda;
void setup() {
  // put your setup code here, to run once:
  govinda.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  govinda.execute();
}