#include <Pin.hpp>
#include <Servo.h>

#define LEFT 14
#define RIGHT 15
#define BOTTOM 16

#define SERVOX 5
#define SERVOY 6

#define TRESHOLD 10
#define DELAY 15
#define INC 0.3

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
  valueBott = photoBott.read();
  valueTop = (valueLeft + valueRight) / 2;

  Serial.print("Left: ");
  Serial.print(valueLeft);
  Serial.print("; Right: ");
  Serial.print(valueRight);
  Serial.print("; Bott: ");
  Serial.print(valueBott);
  Serial.print("; Topp: ");
  Serial.print(valueTop);
  Serial.print("\r\n");


  if (valueLeft > valueRight && valueLeft - valueRight > TRESHOLD)
    servoXPos -= INC * (valueLeft - valueRight);
  else if (valueRight > valueLeft && valueRight - valueLeft > TRESHOLD)
    servoXPos += INC * (valueRight - valueLeft);
  if (valueBott > valueTop && valueBott - valueTop > TRESHOLD)
    servoYPos -= INC * (valueBott - valueTop);
  else if (valueTop > valueBott && valueTop - valueBott > TRESHOLD)
    servoYPos += INC * (valueTop - valueBott);

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
}
