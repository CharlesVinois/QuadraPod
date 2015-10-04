#include <Servo.h>
Servo myservo1;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
Servo myservo2;
int ServoPos1 = 0;    // variable to store the servo position
int ServoPos2 = 0;
// the setup routine runs once when you press reset:
void setup() {
  myservo1.attach(12);  // attaches the servo on pin 3 to the servo object
  myservo2.attach(13);      
}
// the loop routine runs over and over again forever:
void loop(){
  for(ServoPos1 = 0; ServoPos1 < 180; ServoPos1 += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo1.write(ServoPos1);              // tell servo to go to position in variable 'pos' 
    myservo2.write(ServoPos1);  
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
  for(ServoPos1 = 180; ServoPos1>=1; ServoPos1-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo1.write(ServoPos1);              // tell servo to go to position in variable 'pos' 
    myservo2.write(ServoPos1);  
    delay(15);                       // waits 15ms for the servo to reach the position 
  }
}
