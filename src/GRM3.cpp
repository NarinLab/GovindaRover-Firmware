/*
 * GRM3 - Govinda Rover Mark III Firmware
 * Model: ATMega328P Microcontroller Unit (Arduino Nano)
 * License: AGPLv3
 * Researched & Maintained by PRITA & NarinLab, 2021
 * prita.undiknas.ac.id | narin.co.id | tutorkeren.com
 */

#include "GRM3.h"

GRM3::GRM3()
{
  _SERVOX.attach(PIN_SERVO_X);
  _SERVOY.attach(PIN_SERVO_Y);
  _SERVOX_POS = 90;
  _SERVOY_POS = 90;
}
void GRM3::begin()
{
  Serial.begin(115200);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial);

  pinMode(PIN_ENA, OUTPUT);
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);
  pinMode(PIN_ENB, OUTPUT);
  pinMode(PIN_SERVO_X, OUTPUT);
  pinMode(PIN_SERVO_Y, OUTPUT);
}

void GRM3::execute(){
  _serialCommandHandler(Serial);
  lookAt();
}

void GRM3::setDirection(char dir)
{
  switch (dir)
  {
  case 'f':
    digitalWrite(PIN_IN1, LOW);
    digitalWrite(PIN_IN2, HIGH);
    digitalWrite(PIN_IN3, LOW);
    digitalWrite(PIN_IN4, HIGH);
    break;
  case 'b':
    digitalWrite(PIN_IN1, HIGH);
    digitalWrite(PIN_IN2, LOW);
    digitalWrite(PIN_IN3, HIGH);
    digitalWrite(PIN_IN4, LOW);
    break;
  case 'l':
    digitalWrite(PIN_IN1, HIGH);
    digitalWrite(PIN_IN2, LOW);
    digitalWrite(PIN_IN3, LOW);
    digitalWrite(PIN_IN4, HIGH);
    break;
  case 'r':
    digitalWrite(PIN_IN1, LOW);
    digitalWrite(PIN_IN2, HIGH);
    digitalWrite(PIN_IN3, HIGH);
    digitalWrite(PIN_IN4, LOW);
    break;
  
  default:
    digitalWrite(PIN_IN1, HIGH);
    digitalWrite(PIN_IN2, HIGH);
    digitalWrite(PIN_IN3, HIGH);
    digitalWrite(PIN_IN4, HIGH);
    break;
  }
}

void GRM3::setSpeed(uint8_t pwm)
{
  analogWrite(PIN_ENA, pwm);
  analogWrite(PIN_ENB, pwm);
}

void GRM3::setHead(uint8_t x, uint8_t y)
{
  if(x < 0 || x > 180 || y < 0 || y > 180) return;
  _SERVOX_POS = x;
  _SERVOY_POS = y;
}

void GRM3::lookAt()
{
  if ((millis() - _servoCounter) >= SERVO_SPEED) {
    _servoCounter = millis();

    if (_SERVOX_POS > _SERVOX.read()) _SERVOX.write(_SERVOX.read() + 1);
    else if (_SERVOX_POS < _SERVOX.read()) _SERVOX.write(_SERVOX.read() - 1);

    if (_SERVOY_POS > _SERVOY.read()) _SERVOY.write(_SERVOY.read() + 1);
    else if (_SERVOY_POS < _SERVOY.read()) _SERVOY.write(_SERVOY.read() - 1);
  }
}

void GRM3::_serialCommandHandler(HardwareSerial &serial)
{
  StaticJsonDocument<DOCSIZE> doc;
  if (Serial.available()) 
  {
    DeserializationError err = deserializeJson(doc, Serial);
    if (err == DeserializationError::Ok) 
    {
      _commandHandler(doc);
    } 
    else 
    {
      Log.error(F("[_serialCommandHandler] Failed to parse serial: %s" CR) , err.c_str());  
    }
  }
}

void GRM3::_commandHandler(StaticJsonDocument<DOCSIZE> doc)
{
  if(doc["method"] == nullptr) return;
  const char* method = doc["method"].as<const char*>();

  if(strcmp(method, (const char*) "dirc") == 0)
  {
    setDirection(doc["params"]["dir"].as<char>());
  }
  else if(strcmp(method, (const char*) "sped"))
  {
    setSpeed(doc["params"]["pwm"].as<uint8_t>());
  }
  else if(strcmp(method, (const char*) "look"))
  {
    setHead(doc["params"]["x"].as<uint8_t>(), doc["params"]["y"].as<uint8_t>());
  }
}