#include <LiquidCrystal_I2C.h>

#define pinSensor A0
#define adress 0x27
#define column 16
#define line 1
#define pinRelay 9

bool ReadSensor;
bool ReadBefore;

LiquidCrystal_I2C lcd(adress, column, line);

void setup() {
  lcd.init(); //init lcd
  lcd.backlight(); //On light of display
  lcd.clear(); //clear display screen

  pinMode(pinRelay, OUTPUT);
  
}

void loop() {
  if(analogRead(pinSensor) > 700){
    ReadSensor = true;
    lcd.setCursor(0, 0);
    lcd.print("Seco                       ");
  } else{
    digitalWrite(pinRelay, LOW);
    ReadSensor = false;
    lcd.setCursor(0, 0);
    lcd.print("Umido                    ");
  }

  //entering the wet state
  if(ReadSensor != ReadBefore){
    delay(5000); //5 second
    lcd.setCursor(0, 0);
    lcd.print("Irrigando                    ");

    while(analogRead(pinSensor) > 700){
      digitalWrite(pinRelay, HIGH); //relay on
      delay(1000); //0.5 second
      digitalWrite(pinRelay, LOW); // relay off

      delay(5000); //10 second
    }

    ReadSensor = false;
  }

  ReadBefore = ReadSensor;
}
