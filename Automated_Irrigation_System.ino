#include "DFRobot_LCD.h"
DFRobot_LCD lcd(16,2);

// initializing pin modes
int Moisture;
int Level;
int WaterLevel;
int MoistureValue;

int LED_PIN = 10;
int PumpSoil_PIN = 13;
int PumpTank_PIN = 12;
int WaterSensor_PIN = A0;
int MoistureSensor_PIN = A3;

void setup(){
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.setCursor(0,0);
  lcd.print("Automated Irrigation System");
  lcd.setCursor(0,1);
  lcd.print("Team Liban");
  delay(1500);
  lcd.clear();
  pinMode(LED_PIN, OUTPUT);
  pinMode(PumpSoil_PIN, OUTPUT);
  pinMode(PumpTank_PIN, OUTPUT);
  pinMode(MoistureSensor_PIN, INPUT);
  pinMode(WaterSensor_PIN, INPUT);
}

void loop(){
  // put your main code here, to run repeatedly
  WaterLevel = analogRead(WaterSensor_PIN);
  Level = map(WaterLevel,0,1023,0,100);
  MoistureValue = analogRead(MoistureSensor_PIN);
  Moisture = map(MoistureValue,0,1023,0,100);
  control_func();
  display_func();
}

void control_func(){
  if (Level > 55 && Moisture < 55){
    LCD_func();
    digitalWrite(PumpSoil_PIN,HIGH);
    digitalWrite(PumpTank_PIN,LOW);
    digitalWrite(LED_PIN,HIGH);
  } else if (Level < 55 && Moisture >55) {
    LCD_func();
    digitalWrite(PumpSoil_PIN,LOW);
    digitalWrite(PumpTank_PIN,HIGH);
    digitalWrite(LED_PIN,LOW);
    //delay(500);
  } else if (Level > 55 && Moisture >55) {
    LCD_func();
    digitalWrite(PumpSoil_PIN,LOW);
    digitalWrite(PumpTank_PIN,LOW);
    digitalWrite(LED_PIN,LOW);
    //delay(500);
  } else if (Level < 55 && Moisture <55){
    LCD_func();
    digitalWrite(PumpSoil_PIN,HIGH);
    digitalWrite(PumpTank_PIN,HIGH);
    digitalWrite(LED_PIN,HIGH);
    //delay(500);
  }
}

void display_func(){
  if (Level > 55 && Moisture < 55){
    virtual_terminal();

  } else if (Level < 55 && Moisture >55) {
    virtual_terminal();
    
  } else if (Level > 55 && Moisture >55) {
    virtual_terminal();
    
  } else if (Level < 55 && Moisture <55){
    virtual_terminal();
  }
}

void LCD_func(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tank Level:");
  lcd.print(Level);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("Moisture:");
  lcd.print(Moisture);
  lcd.print("%");
}

void virtual_terminal(){
  lcd.clear();
  Serial.println(F("Water Level:" ));
  Serial.println(Level);
  Serial.println(F("Moisture:" ));
  Serial.println(Moisture);
}
