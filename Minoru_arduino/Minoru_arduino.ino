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
double Kp = 1, Ki = 0, Kd = 0;

PID PID_xAxis(&x, &set_x, &goal_x, Kp, Ki, Kd, DIRECT);
long startTime = 0;
String inputString = "";

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(BAUD_RATE);
  PID_xAxis.SetMode(AUTOMATIC); //turn the PID on
  PID_xAxis.SetOutputLimits(-1000.0,1000.0);
  PID_xAxis.SetSampleTime(600);
  TiltMotor.attach(5);
  PanMotor.attach(6);
  TiltMotor.writeMicroseconds(TILT_HOME);
  PanMotor.writeMicroseconds(PAN_HOME);
  //delay(10000);
}
int temp;
void loop()
{
#ifdef DEBUG
  if ((millis() - startTime) > 50)
    digitalWrite(13, LOW);
#endif
    
    PID_xAxis.Compute();
    temp = constrain(map(PanMotor.read(),0,180,1000,2000) + round((int)set_x), 1000, 2000);
    PanMotor.write(temp);
}

void serialEvent()
{
  inputString = Serial.readStringUntil(',');
//  Serial.println("hello");
  if (inputString.startsWith("x"))
  {
//    Serial.println("hello1");
    x = (inputString.substring(1)).toFloat();
//    Serial.println("hello2");
    inputString = Serial.readStringUntil('\n');
//    Serial.println("hello3");
    y = inputString.toFloat();
//    Serial.println("hello4");
#ifdef DEBUG
    digitalWrite(13, HIGH);
    startTime = millis();
    String msg = "";
    /*
    msg.concat(x);
    msg.concat(",");
    msg.concat(y);
    msg.concat(",");
    msg.concat(goal_x);
    msg.concat(",");
    msg.concat(goal_y);
    */
    msg.concat(temp);
    Serial.println(msg);
#endif
  }
  else if (inputString.startsWith("c"))
  {
    goal_x = inputString.substring(1).toFloat();
    inputString = Serial.readStringUntil('\n');
    goal_y = inputString.toFloat();
    Serial.println("goals set");
  }
}
