// ______TOUCH SENSOR _______

int led =2;;
oid setup() {
  // put your setup code here, to run once:
serial.begin(115200);
pinMode(led,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
// serial.println(touchRead(T0));
if(touchRead(T0)<30){
  digitalWrite(led,HIGH);
}
else{ 
  digitalWrite(led,LOW);
}
delay(200); 
}

// ______SERVO______
#include<ESP32Servo.h>
Servo myServo;
int servopin=18;
void setup() {
  myServo.attach(servopin);
  Serial.begin(115200);
}
void loop (){
  if(Serial.available()){
int angle= Serial.parseInt();
myServo.write(angle);
  }

}

// _______CONTROL-RELAY_____
int relay=2;
void setup() {
  pinMode(relay,OUTPUT);
  Serial.begin(115200);
}

void loop(){
  if(serial.available()){
    String cmd = Serial.readString();
    if (cmd == "on"){
      digitalWrite(relay,HIGH);
    }else if (cmd == "off")
    digitalWrite(relay,LOW);
  }
}
 