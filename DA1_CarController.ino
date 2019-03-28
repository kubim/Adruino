#include <SoftwareSerial.h>
#define TX_PIN  13
#define RX_PIN  12

#include <Servo.h>
Servo myservo;
int quangtro = A0;
int servoPin = 9;

SoftwareSerial HC06(RX_PIN, TX_PIN);
// Động cơ 1 
int enA = 8;
int in1 = 7;
int in2 = 6; 

//động cơ 2 
int in3 = 5; 
int in4 = 4; 
int enB = 3;
void DCA_Tien(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW); 
  analogWrite(enA, 255);
}
void DCA_Lui(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); 
  analogWrite(enA, 255);
}
void DCA_Stop(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW); 
}
void DCB_Tien(){
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW); 
  analogWrite(enB, 255);
}
void DCB_Lui(){
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  analogWrite(enB, 255);
}
void DCB_Stop(){
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW); 
}
void Stop(){
  DCA_Stop();
  DCB_Stop();
}
void tien(){
    DCB_Tien();
  DCA_Tien();

}
void lui(){
  DCA_Lui();
  DCB_Lui();
}
void trai(){
  DCA_Tien();
  DCB_Lui();
  
}
void phai(){
  DCB_Tien();
  DCA_Lui();
}
void bia(){
  int servoPos = map(0, 0, 1023, 0, 180);
    myservo.write(servoPos);
    int giatriQuangtro = analogRead(quangtro);// đọc giá trị quang trở
    Serial.println(giatriQuangtro);
    if(giatriQuangtro>850){
    servoPos = map(400, 0, 1023, 0, 180);
    myservo.write(servoPos);
    delay(1000);
    }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  HC06.begin(9600);
  myservo.attach(servoPin); 
  
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
    
  if(HC06.available()){
    char blu = HC06.read();
    Serial.write(blu);
    Serial.println();
    if(blu == '0'){
      Stop();
    }
    if(blu == '1'){
        tien();
    }
    if(blu == '2'){
        phai();
    }
    if(blu == '3'){
       lui();
    }
    if(blu == '4'){
       trai();
    }
    bia();
  }
  else
  {
    bia();
  }
}
