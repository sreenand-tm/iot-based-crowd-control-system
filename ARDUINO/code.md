#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include<Servo.h>
#include<SoftwareSerial.h>
SoftwareSerial espSerial(2,3);
LiquidCrystal_I2C lcd(0x27, 16, 2); 
Servo myServo;
const int entryPIR = 8;
const int exitPIR = 7;
int count = 0;
bool entryReady = true;
bool exitReady = true;
unsigned long lastEntryTime = 0;
unsigned long lastExitTime = 0;
const int debounceDelay = 1000;
int speed;
void setup() {
    pinMode(entryPIR, INPUT);
    pinMode(exitPIR, INPUT);
    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.init();
    lcd.backlight();
    myServo.attach(5);
    myServo.write(0);
    espSerial.begin(9600);
    lcd.setCursor(0, 0);
    lcd.print("People Count: 0");
    lcd.setCursor(0, 1);
    lcd.print("Enter y  Exit y");
}

void loop() {
    int entrySensor = digitalRead(entryPIR);
    int exitSensor = digitalRead(exitPIR);
    bool countUpdated = false;
    if (entrySensor == HIGH && entryReady) {
        count++;
        entryReady = false;
        lastEntryTime = millis();
        countUpdated = true;
        lcd.setCursor(0, 1);
        lcd.print("Enter n");
    }
    if (!entryReady && entrySensor == LOW && millis() - lastEntryTime > debounceDelay) {
        entryReady = true;
        lcd.setCursor(0, 1);
        lcd.print("Enter y ");
    }
    if (exitSensor == HIGH && exitReady && count > 0) {
        count--;
        exitReady = false;
        lastExitTime = millis();
        countUpdated = true;
        lcd.setCursor(9, 1);
        lcd.print("Exit n");
    }
    if (!exitReady && exitSensor == LOW && millis() - lastExitTime > debounceDelay) {
        exitReady = true;
        lcd.setCursor(9, 1);
        lcd.print("Exit y ");
    }
    if (countUpdated) {
        Serial.print("People Count: ");
        Serial.println(count);
        Serial.print("Count:");
        Serial.println(count);
        espSerial.print(count); 
        espSerial.print("\r\n");
        lcd.setCursor(0, 0);
        lcd.print("People Count: ");
        lcd.print(count);
        lcd.setCursor(0, 1);
        lcd.print(entryReady ? "Enter y " : "Enter n  ");
        lcd.print(exitReady ? "Exit y" : "Exit n");
    }
    if(count>10){
      lcd.setCursor(0,0);
       lcd.print("capacity Max");
      lcd.setCursor(0,1);
      lcd.print("reduce");
    }
    if (count==0){
      speed=0;
    }
    speed=map(count,1,10,0,180);
    myServo.write(speed);
    delay(100);
}
