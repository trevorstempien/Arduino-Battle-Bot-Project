#include <Servo.h>  // servo library  Note including this library diables PWM on pins 9, 10 Analogue writes will no longer
                     // work there but digital will
Servo servo_R;   //assign servos Right and Left Side of Robot
Servo servo_L;
const int leftSensor = 10;     // Assign sensor pins for two down sensors
const int rightSensor = 9;
int lsensorState = 0;          // Initialize sensor variable 
int rsensorState = 0;
const int trigPin = 5;           //connects to the echo pin on the distance sensor       
const int echoPin = 6;           //connects to the trigger pin on the distance sensor     

float distance = 0;               //stores the distance measured by the distance sensor

void setup(){  //do this setup once
  pinMode(leftSensor, INPUT);   // Declare assigned sensor pins as input
  pinMode(rightSensor, INPUT);
  servo_R.attach(12);    // attach two servos to pins 12 and 13
  servo_L.attach(13);
  Serial.begin(9600);  
   pinMode(trigPin, OUTPUT);   //the trigger pin will output pulses of electricity 
  pinMode (echoPin, INPUT);    //the echo pin will measure the duration of pulses coming back from the distance sensor
  pinMode (9, INPUT);
  pinMode (8, INPUT);// set serial monitor baud rate for output sensor state testing
 delay (5000);
}

void loop(void ){
  
//sensors(); 

 distance = getDistance();
  Serial.print(distance);     //print the distance that was measured
  Serial.println("in");      //print units after the distance
  //Serial.print;

 if(distance >5 && distance <15 ){                         //if the object is closer than 10 inches
      servo_R.write(180);   //right motor counterclockwise (Full Speed backward)
  servo_L.write(0); //left motor Clockwise for forward
  delay(100);
  distance = getDistance(); 

 }

 
 else
 {
   servo_R.write(180);   //right motor clockwise (Full Speed forward)
   servo_L.write(180); //left motor counterClockwise for forward
   delay(100);
   distance = getDistance();
 }

}  //end void loop

//------------------FUNCTIONS-------------------------------

//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR
float getDistance()
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calcualtedDistance;         //variable to store the distance calculated from the echo time
  
  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor

  calcualtedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)
  
  return calcualtedDistance;
}//send back the distance that was calculated
float sensors(){
  rsensorState = digitalRead(rightSensor);  //read right sensor
  lsensorState = digitalRead(leftSensor);   //read left sensor
  if(rsensorState == HIGH){  //If Right sensor detects table edge green indicator light off
  servo_R.write(180); //right motor counterclockwise reverse
  servo_L.write(0);  //left motor Clockwise for reverse
  delay(500);  //  .5 second delay
 servo_L.write(0);  //left motor Clockwise for reverse
    servo_R.write(0);   //right motor clockwise forward
    delay(250);  //  .25 second delay
    Serial.println("Right Sensor");
  }   else if(lsensorState == HIGH){           //If Left sensor detects table edge
  servo_R.write(180); //right motor counterclockwise reverse
  servo_L.write(0);  //left motor Clockwise for reverse
  delay(500);  //  .5 second delay
    servo_R.write(180);    // spin right motor backwards
    servo_L.write(180);    // spin Left motor forwards
    delay(250);  //  .25 second delay
    Serial.println("Left Sensor") ;  } 
  else  {   //drive forward green lights on both sensors LOW
  servo_R.write(0);   //right motor clockwise forward
  servo_L.write(180); 
}}
//end of void loop

