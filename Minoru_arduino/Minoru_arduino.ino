#include <PID_v1.h>
#include <Servo.h> 

#define BAUD_RATE 9600
#define TILT_HOME 139
#define PAN_HOME 75

Servo tiltMotor,panMotor;  // create servo object to control a servo 

int x = 0,y= 0;

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() 
{ 
  Serial.begin(BAUD_RATE);
  Input =
  Setpoint = 100;
  myPID.SetMode(AUTOMATIC); //turn the PID on
  tiltMotor.attach(5); 
  panMotor.attach(6);
  tiltMotor.write(TILT_HOME);
  panMotor.write(PAN_HOME);
  delay(1000);
}

void loop() 
{
  while (Serial.available())
  {
    String inData = "";
    char recieved = ' '; 

    if (Serial.read() == 'x')
    {
      do{
        recieved = (char) Serial.read();
        if (recieved != char(-1))
          inData += recieved;
      }while (recieved != ',');
      x = inData.toInt();
      inData = "";

      do{
        recieved = (char) Serial.read();
        if (recieved != char(-1))
          inData += recieved;
      }while ( recieved != '\n');
      y = inData.toInt();
    }

  }
  
  Input = analogRead(PIN_INPUT);
  myPID.Compute();
  analogWrite(PIN_OUTPUT, Output);

  #ifdef DEBUG
  if (x > 0)
  {
    Serial.print(x);
    Serial.print(",");
    Serial.println(y);
  }
  #endif
  delay(15);
  
  /*
  for(pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    tiltMotor.write(pos);              // tell servo to go to position in variable 'pos' 
    panMotor.write(pos);
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(pos = 180; pos>=0; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    tiltMotor.write(pos);              // tell servo to go to position in variable 'pos' 
    panMotor.write(pos);
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  */
  
} 

