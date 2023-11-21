#include <Pin.hpp>
#include <Servo.h>

#define LEFT 15
#define RIGHT 14
#define BOTTOM 16

#define SERVOX 5
#define SERVOY 6

#define TRESHOLD 10
#define DELAY 50
#define INC 0.01

AnalogPin photoLeft(LEFT, AnalogPin::Mode::Input);
AnalogPin photoRigh(RIGHT, AnalogPin::Mode::Input);
AnalogPin photoBott(BOTTOM, AnalogPin::Mode::Input);

Servo servoX;
Servo servoY;

int servoXPos = 90;
int servoYPos = 90;

int valueLeft;
int valueRight;
int valueBott;
int valueTop;

void setup() {
  Serial.begin(9600);
  servoX.attach(SERVOX);
  servoY.attach(SERVOY);
  servoX.write(servoXPos);
  servoY.write(servoYPos);
}

void loop() {
  valueLeft = photoLeft.read();
  valueRight = photoRigh.read();
  valueTop = photoBott.read();
  valueBott = (valueLeft + valueRight) / 2 + 20;

  //Serial.print("Left: ");
  //Serial.print(valueLeft);
  //Serial.print("; Right: ");
  //Serial.print(valueRight);
  //Serial.print("; Bott: ");
  //Serial.print(valueBott);
  //Serial.print("; Topp: ");
  //Serial.print(valueTop);
  //Serial.print("\r\n");


  if (valueLeft != valueRight && abs(valueLeft - valueRight) > TRESHOLD)
    servoXPos = (int)(servoXPos + INC * (valueLeft - valueRight)) + 0.5;
  if (valueTop != valueBott && abs(valueTop - valueBott) > TRESHOLD / 2)
    servoYPos = (int)(servoYPos - INC * (valueTop - valueBott)) + 0.5;

  if (servoYPos < 0)
    servoYPos = 0;
  else if (servoYPos > 180)
    servoYPos = 180;
  if (servoXPos < 0)
    servoXPos = 0;
  else if (servoXPos > 180)
    servoXPos = 180;

  servoX.write(servoXPos);
  servoY.write(servoYPos);

  delay(DELAY);
}
