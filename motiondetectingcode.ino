#include <Servo.h>

Servo myservo;  
int pos = 0;        
int calibrationTime = 30;
long unsigned int lowIn;        
long unsigned int pause = 5000; 

boolean lockLow = true;
boolean takeLowTime; 

int pirPin = 12;           
int pirPos = 13;         

void setup(){
  myservo.attach(4);   
  Serial.begin(9600);   
  pinMode(pirPin, INPUT);
  pinMode(pirPos, OUTPUT);
  digitalWrite(pirPos, HIGH);

  Serial.println("calibrating sensor ");
  for(int i = 0; i < calibrationTime; i++){
    Serial.print(calibrationTime - i);
    Serial.print("-");
    delay(1000);
  }
  Serial.println();
  Serial.println("done");

  while (digitalRead(pirPin) == HIGH) {
    delay(500);
    Serial.print(".");     
  }
  Serial.print("SENSOR ACTIVE");
}

void loop(){

  if(digitalRead(pirPin) == HIGH){ 

    for(pos = 0; pos < 180; pos += 1) 
    {                                                
      myservo.write(pos);                   
      delay(5);                                   
    }
    for(pos = 180; pos>=1; pos-=1)    
    {                               
      myservo.write(pos);                  
      delay(5);                                 
    }
   
    if(lockLow){ 
      lockLow = false;           
      Serial.println("---");
      Serial.print("motion detected at ");
      Serial.print(millis()/1000);
      Serial.println(" sec");
      delay(50);
    }        
    takeLowTime = true;
  }

  if(digitalRead(pirPin) == LOW){      

    if(takeLowTime){
      lowIn = millis();
      takeLowTime = false;
    }

    if(!lockLow && millis() - lowIn > pause){
      lockLow = true;                       
      Serial.print("motion ended at "); 
      Serial.print((millis() - pause)/1000);
      Serial.println(" sec");
      delay(50);
    }
  }
}