
#include <defirobo.h>
#include "defirobo.h"

String command;
String device;

void setup() 
{
  
  Serial.begin(9600);
  BT1.begin(9600);
  
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  
  pinMode(lineFollowSensor0, INPUT);
  pinMode(lineFollowSensor1, INPUT);
  pinMode(lineFollowSensor2, INPUT);
  pinMode(lineFollowSensor3, INPUT);
  pinMode(lineFollowSensor4, INPUT);
  
  
  leftServo.attach(5);
  rightServo.attach(3);
  
  BT1.print("check the PID constants to be sent to Robot");
  BT1.println('\n');

  while (digitalRead(buttonPin) && !mode)
  {  
    checkBTcmd();
    manualCmd ();    
    command = "";  
  }
  checkPIDvalues();
  mode = STOPPED;
}

void loop() // básico mãe
{
    
  while (digitalRead(buttonPin) && !mode)
  { }
  
  readLFSsensors();    
    switch (mode)
  {
    case STOPPED: 
      motorStop();
      BT1.print("The End");
      ledBlink();
      previousError = error;
      break;

    case NO_LINE:  
      motorStop();
      motorTurn(LEFT, 180);
      previousError = 0;
      break;

    case FOLLOWING_LINE:     
      calculatePID();
      motorPIDcontrol();    
      break;     
  }
}
//pg