#include <Pin.hpp>
#include <Servo.h>

#define LEFT 14
#define RIGHT 15
#define BOTTOM 16

#define POT 17

#define SERVOX 5
#define SERVOY 6

AnalogPin photoLeft(LEFT, AnalogPin::Mode::Input);
AnalogPin photoRigh(RIGHT, AnalogPin::Mode::Input);
AnalogPin photoBott(BOTTOM, AnalogPin::Mode::Input);
AnalogPin pot(POT, AnalogPin::Mode::Input);


Servo servoX;
Servo servoY;

int servoXPos = 90;
int servoYPos = 90;

void setup() {
  Serial.begin(9600);
  servoX.attach(SERVOX);
  servoY.attach(SERVOY);
  servoX.write(servoXPos);
  servoY.write(servoYPos);
}
int val;
void loop() {
  val = pot.read();
  val = map(val, 0, 1023, 0, 180);
  servoX.write(val);
  servoY.write(val);
  delay(15);
}
