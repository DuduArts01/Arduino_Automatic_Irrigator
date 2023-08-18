#include <LiquidCrystal_I2C.h>

#define pinSensor A0
#define pinLedRed 2
#define pinLedBlue 3
#define pinLedGreen 8
#define pinRelay 10
#define adress 0x27
#define column 16
#define line 2

bool ReadSensor;
bool ReadBefore;

LiquidCrystal_I2C lcd(adress, column, line);

void setup() {
  pinMode(pinLedRed, OUTPUT);
  pinMode(pinLedBlue, OUTPUT);
  pinMode(pinLedGreen, OUTPUT);

  lcd.init(); //init lcd
  lcd.backlight(); //On light of display
  lcd.clear(); //clear display screen
  
}

void loop() {
  if(analogRead(pinSensor) > 700){
    digitalWrite(pinLedRed, HIGH);
    digitalWrite(pinLedGreen, LOW);
    ReadSensor = true;
    lcd.setCursor(0, 0);
    lcd.print("Seco         ");
  } else{
    digitalWrite(pinLedRed, LOW);
    digitalWrite(pinLedGreen, HIGH);
    //digitalWrite(pinSolenoide, LOW);
    ReadSensor = false;
    lcd.setCursor(0, 0);
    lcd.print("Umido        ");
  }

  //entering the wet state
  if(ReadSensor != ReadBefore){
    delay(15000); //5 second
    
    digitalWrite(pinLedRed, LOW); //Low Red
    digitalWrite(pinLedBlue, HIGH); //HIGH Blue
    lcd.setCursor(0, 0);
    lcd.print("Irrigando        ");

    while(analogRead(pinSensor) > 700){
      digitalWrite(pinRelay, HIGH); //relay on
      delay(500); //0.5 second
      digitalWrite(pinRelay, LOW); // relay off

      delay(10000); //10 second
    }

    digitalWrite(pinLedBlue, LOW); //Led Blue off
    ReadSensor = false;
  }

  ReadBefore = ReadSensor;
}
