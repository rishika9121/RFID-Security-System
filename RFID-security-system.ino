#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
Servo myServo;
 
#define SS_PIN 10
#define RST_PIN 9
int redLed = 5;
int greenLed = 4;
int buzzer = 2;

MFRC522 mfrc522(SS_PIN, RST_PIN);
void setup() 
{
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  SPI.begin(); 
  mfrc522.PCD_Init(); 
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  myServo.attach(3);
  myServo.write(0);
  

}
void loop() 
{
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "E2 6A 86 19") 
  {
    Serial.println("Authorized access");
    Serial.println();
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
    delay(3000);
    myServo.write(90);
    delay(5000);
    myServo.write(0);
    digitalWrite(greenLed, LOW);
  }
 
 else   {
    Serial.println(" Access denied");
    digitalWrite(redLed, HIGH);
    digitalWrite(buzzer, HIGH);
    digitalWrite(greenLed, LOW);
    delay(3000);
    digitalWrite(buzzer, LOW);
    digitalWrite(redLed, LOW);
    
       
  }
} 
