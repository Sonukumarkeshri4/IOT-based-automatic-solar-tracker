
#include <Servo.h>


Servo trackerLR; //left/right movement servo 
Servo trackerTB;  //top/bottom movement servo 

//Photoresistor Pins
int leftLDRpin = A1;  //Analog pins
int bottomLDRpin = A2;
int rightLDRpin = A3;

//Photoresistors
int rightLDR = 0;  //Variables for the sensor values
int leftLDR = 0;
int bottomLDR = 0;
int topLDR = 0;


int horizontalError = 0;
int verticalError = 0;

int trackerLRPos = 0;    //Create a variable to store the servo position
int trackerTBPos = 0;

unsigned long currentMillis = 0;
unsigned long startMillis = 0;
int interval = 2000;

//write your main code here
void setup() 
{ 
 startMillis = millis();
 tone(2, 2637);
 delay(200);
 noTone(2);
 delay(50);
 tone(2, 2637);
 delay(300);
 noTone(2);
 delay(100);
 tone(2, 2637);
 delay(200);
 noTone(2);
 delay(200);
 tone(2, 2093);
 delay(200);
 noTone(2);
 delay(100);
 tone(2, 2637);
 delay(100);
 noTone(2);
 delay(300);
 tone(2, 3136);
 delay(200);
 noTone(2);
 delay(600);
 tone(2, 1568);
 delay(300);
 noTone(2);
 delay(1000);
 //Servo pins
 trackerLR.attach(10);  
 trackerTB.attach(11);
 Serial.begin(9600); 
 pinMode(2, OUTPUT);
 pinMode(3, OUTPUT);
 pinMode(4, OUTPUT);
 pinMode(5, OUTPUT);
 pinMode(6, OUTPUT);
 pinMode(7, OUTPUT);

}

void loop() 
{ 
  currentMillis = millis();
  if (currentMillis - startMillis >= interval)  
  {
    tone(2, 1000);
    digitalWrite(6, HIGH);
    delay (100);
    noTone (2);
    digitalWrite(6, LOW);
    startMillis = currentMillis;  
  }
  //Values of the right and left sensors
  rightLDR = analogRead(rightLDRpin);    
  leftLDR = analogRead(leftLDRpin);
  bottomLDR = analogRead(bottomLDRpin);
  
  Serial.print("rightLDR"); Serial.print(rightLDR); Serial.print(" ");
  Serial.print("leftLDR");Serial.print(leftLDR);Serial.print(" ");
  Serial.print("bottomLDR");Serial.print(bottomLDR);Serial.print(" ");
  Serial.println("");
  horizontalError = rightLDR - leftLDR;  //difference between the two sensors.
  
  if(horizontalError>50)  //if the error is greater than 20 then move the tracker to the right
  { 
    digitalWrite(3,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
      trackerLRPos--;
      trackerLRPos = constrain (trackerLRPos, 0,179);
      trackerLR.write(trackerLRPos);  
      delay(10);
      noTone(2);
  }
  
  else if(horizontalError<-50)  //If the error is less than -20 then move the tracker to the left
  {
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
      trackerLRPos++;
      
      trackerLRPos = constrain (trackerLRPos, 0,179 );
      trackerLR.write(trackerLRPos);

  }


  topLDR = (rightLDR + leftLDR)/2; //Average value of right and left sensors


  verticalError = topLDR - bottomLDR; //Difference between top and bottom readings
  
  if(verticalError>40)  //If the error is greater than 50 then move the tracker up
  {
    digitalWrite(3,LOW);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
      trackerTBPos++;
      
      trackerTBPos = constrain (trackerTBPos, 10,120);
      trackerTB.write(trackerTBPos);  
  }
  
  else if(verticalError<-40)  //If the error is less than -50 then move the tracker down
  {
    digitalWrite(3,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
      trackerTBPos--;
      trackerTBPos = constrain (trackerTBPos, 10,120);
      trackerTB.write(trackerTBPos); 
  }
 delay(25);
}
