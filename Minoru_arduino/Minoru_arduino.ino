#define DEBUG
#include <PID_v1.h>
#include <Servo.h>

#define BAUD_RATE 57600
#define TILT_HOME 1772
#define PAN_HOME 1337
#define DEBUG
Servo TiltMotor, PanMotor; // create servo object to control a servo

double x = 1.0, y = 3.0, set_x = 0.0, set_y = 0.0, goal_x = 0.0, goal_y = 0.0;

//initial tuning parameters
float Kp = 322, Ki = 5, Kd = 1;

PID PID_xAxis(&x, &set_x, &goal_x, Kp, Ki, Kd, DIRECT);
long startTime = 0;
String inputString = "";

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(BAUD_RATE);
  //inputString.reserve(20);
  PID_xAxis.SetMode(AUTOMATIC); //turn the PID on
  TiltMotor.attach(5);
  PanMotor.attach(6);
  TiltMotor.writeMicroseconds(TILT_HOME);
  PanMotor.writeMicroseconds(PAN_HOME);
  //delay(10000);
}

void loop()
{
#ifdef DEBUG
  if ((millis() - startTime) > 50)
    digitalWrite(13, LOW);
#endif
  
    PID_xAxis.Compute();
    int temp = constrain(PanMotor.read()+ round((int)set_x), 1000, 2000);
    PanMotor.write(PanMotor.read()+ set_x);

}

void serialEvent()
{
  inputString = Serial.readStringUntil(',');
  if (inputString.startsWith("x"))
  {
    x = (inputString.substring(1)).toFloat();
    inputString = Serial.readStringUntil('\n');
    y = inputString.toFloat();
#ifdef DEBUG
    digitalWrite(13, HIGH);
    startTime = millis();
#endif
  }
  else if (inputString.startsWith("c"))
  {
    goal_x = inputString.substring(1).toFloat();
    inputString = Serial.readStringUntil('\n');
    goal_y = inputString.toFloat();
  }
}
