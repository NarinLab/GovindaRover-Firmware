#include <ArduinoJson.h>
#include <Servo.h>
#include "header.h"

void setup(){
  actuator_setup();
  serial_setup();  
}

void loop(){
  actuator_set_camera();
}
