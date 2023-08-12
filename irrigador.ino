#define pinSensor A0
#define pinLedRed 2
#define pinLedBlue 3
#define pinLedGreen 8
#define pinRelay 10

bool ReadSensor;
bool ReadBefore;

void setup() {
  pinMode(pinLedRed, OUTPUT);
  pinMode(pinLedBlue, OUTPUT);
  pinMode(pinLedGreen, OUTPUT);

}

void loop() {  
  if(analogRead(pinSensor) > 700){
    digitalWrite(pinLedRed, HIGH);
    digitalWrite(pinLedGreen, LOW);
    ReadSensor = true;

  } else{
    digitalWrite(pinLedRed, LOW);
    digitalWrite(pinLedGreen, HIGH);
    //digitalWrite(pinSolenoide, LOW);
    ReadSensor = false;
  }

  //entering the wet state
  if(ReadSensor != ReadBefore){
    delay(5000); //5 second
    
    digitalWrite(pinLedRed, LOW); //Low Red
    digitalWrite(pinLedBlue, HIGH); //HIGH Blue

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
