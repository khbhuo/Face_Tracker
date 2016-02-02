#include <PID_v1.h>
#include <Servo.h> 

#define BAUD_RATE 9600
#define TILT_HOME 1772
#define PAN_HOME 1337
#define DEBUG
Servo tiltMotor,panMotor;  // create servo object to control a servo 

double x = 1.0,y= 3.0,set_x = 0.0, set_y =0.0, goal_x= 0.0,goal_y= 0.0;

//initial tuning parameters
float Kp=322, Ki=5, Kd=1;

PID PID_xAxis(&x, &set_x, &goal_x, Kp, Ki, Kd, DIRECT);
String inputString = "";

void setup() 
{ 
  Serial.begin(BAUD_RATE);
  //inputString.reserve(20);
  PID_xAxis.SetMode(AUTOMATIC); //turn the PID on
  tiltMotor.attach(5); 
  panMotor.attach(6);
  tiltMotor.writeMicroseconds(TILT_HOME);
  panMotor.writeMicroseconds(PAN_HOME);
  //delay(10000);
}

void loop() 
{
//  Serial.write("he");
  
  /*
  PID_xAxis.Compute();
  int temp = constrain(panMotor.read()+ round((int)set_x), 1000, 2000);
  panMotor.write(panMotor.read()+ set_x);

  #ifdef DEBUG
  if (x > 0)
  {
    Serial.print(panMotor.read());
    Serial.print(",");
    Serial.println(panMotor.read());
  }
  #endif
  */

  {
    Serial.print(x);
    Serial.print(",");
    Serial.println(y);
  }
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
  delay(10);
} 

void serialEvent()
{
  inputString = Serial.readStringUntil(',');
  if (inputString.startsWith("x"))
  {
    x = (inputString.substring(1)).toFloat();
    inputString = Serial.readStringUntil('\n');
    y = inputString.toFloat();
  }
  else if (inputString.startsWith("c"))
  {
    x = inputString.substring(1).toFloat();
    inputString = Serial.readStringUntil('\n');
    y = inputString.toFloat();
  }
/*
  while(!Serial.available());  
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
      x = (float)inData.toInt();
      inData = "";

      do{
        recieved = (char) Serial.read();
        if (recieved != char(-1))
          inData += recieved;
      }while ( recieved != '\n');
      y = (float)inData.toInt();
    }
    else if(Serial.read() == 'c')
    {
      do{
        recieved = (char) Serial.read();
        if (recieved != char(-1))
          inData += recieved;
      }while (recieved != ',');
      goal_x = (float)inData.toInt();
      inData = "";

      do{
        recieved = (char) Serial.read();
        if (recieved != char(-1))
          inData += recieved;
      }while ( recieved != '\n');
      goal_y = (float)inData.toInt();
    }

  }*/
}
