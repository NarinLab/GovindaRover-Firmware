/*
 * GRM3 - Govinda Rover Mark III Firmware
 * Model: ATMega328P Microcontroller Unit (Arduino Nano)
 * License: AGPLv3
 * Researched & Maintained by PRITA & NarinLab, 2021
 * prita.undiknas.ac.id | narin.co.id | tutorkeren.com
 */

#ifndef GRM3_h
#define GRM3_h
#include "Arduino.h"
#include <ArduinoLog.h>
#include <ArduinoJson.h>

#define DOCSIZE 64
#define countof(a) (sizeof(a) / sizeof(a[0]))
#define COMPILED __DATE__ " " __TIME__

#define PIN_ENA 5
#define PIN_IN1 4
#define PIN_IN2 7
#define PIN_IN3 8
#define PIN_IN4 10
#define PIN_ENB 6
#define PIN_SERVO_X 3
#define PIN_SERVO_Y 9


class GRM3
{
  public:
    GRM3();
    void begin();
    void execute();
    void setDirection(char dir);
    void setSpeed(uint8_t pwm);
    void lookAt(uint8_t x, uint8_t y);
  private:
    void _serialCommandHandler(HardwareSerial &serial);
    void _commandHandler(StaticJsonDocument<DOCSIZE> doc);
};

#endif