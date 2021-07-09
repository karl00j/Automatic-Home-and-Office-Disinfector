#include <LiquidCrystal.h>
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

//for first Ultrasonic sensor
const int trigPin = 7;
const int echoPin = 6;

//for second Ultrasonic sensor
const int trigPin1 = 5;
const int echoPin1 = 4;

//for addition button
const int pushButton = 2;
int buttonRead = 0;

//for subtraction button
const int pushButton1 = 3;
int buttonRead1 = 0;

//for buzzer
const int buzzer = 10;

const int led = 9;
const int led1 = 8;
const int output = 11;




class RoomDisinfector{

  public:

    int incomingGuests(int count){
      int duration, distance;
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);

      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      duration = pulseIn(echoPin, HIGH);
      distance = (duration*0.034)/2;

      if(distance <= 12){
        count = count + 1;
        digitalWrite(led, HIGH);
        delay(500);
        digitalWrite(led, LOW);
      }
      return count;
    }

    int outgoingGuests(){
      int duration1, distance1;
      int val=0;
      digitalWrite(trigPin1, LOW);
      delayMicroseconds(2);

      digitalWrite(trigPin1, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin1, LOW);

      duration1 = pulseIn(echoPin1, HIGH);
      distance1 = (duration1*0.034)/2;

      if(distance1 <= 12){
          val = val+1;
          digitalWrite(led1, HIGH);
          delay(500);
          digitalWrite(led1, LOW);
        }

      buttonRead = digitalRead(pushButton);
      buttonRead1 = digitalRead(pushButton1);

      if (buttonRead == HIGH){
       val = val + 1;
       digitalWrite(led1, HIGH);
       delay(500);
       digitalWrite(led1, LOW);
      }

      if(buttonRead1 == HIGH){
       val = val-1;
       digitalWrite(led1, HIGH);
       delay(500);
       digitalWrite(led1, LOW);
      }
      return val;
    }

    void alarm(){
      tone(buzzer, 450);
      delay(3000);
      noTone(buzzer);

    }

    void lcdDisplay(int passedVal, int passedVal1){
     Serial.print("Incoming: ");
     Serial.println(passedVal);

     Serial.print("Outgoing: ");
     Serial.println(passedVal1);

     lcd.setCursor(12, 0);
     lcd.print(passedVal);
     lcd.setCursor(10, 1);
     lcd.print(passedVal1);



     }




};




void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(pushButton, INPUT);
  pinMode(pushButton1, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);

  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Population: ");
  lcd.setCursor(0, 1);
  lcd.print("Outgoing: ");
}

void loop() {
  int count = 0;
  RoomDisinfector r;

  int temp, temp1;
  temp = r.incomingGuests(count);
  temp1 = r.outgoingGuests();

  r.lcdDisplay(temp, temp1);

  if(temp <= temp1){
    r.alarm();
    delay(300000);
    digitalWrite(output, HIGH);
    count = 0;
  }
}
