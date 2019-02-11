const int analogInPin  = A0;
int sensorAnalogValue  = 0;
const int digitalInPin = 2;
int sensorDigitalValue = 0;
const int level_1 = 7;
const int level_2 = 6;
const int level_3 = 5;
const int level_4 = 4;
const int level_5 = 3;
 
  
  
void setup() 
{
  Serial.begin(9600);
  Serial.println("Microphone Test" );
}

void loop() 
{
  int volume  = analogRead(analogInPin) - 500;
  
  
  if(volume < 20)
  {
    digitalWrite(level_1, HIGH);
    digitalWrite(level_2, LOW);
    digitalWrite(level_3, LOW);
    digitalWrite(level_4, LOW);
    digitalWrite(level_5, LOW);
  }
  if((volume >= 20) && (volume < 40))
  {
    digitalWrite(level_1, HIGH);
    digitalWrite(level_2, HIGH);
    digitalWrite(level_3, LOW);
    digitalWrite(level_4, LOW);
    digitalWrite(level_5, LOW);
  }
  if((volume >= 40) && (volume < 60))
  {
    digitalWrite(level_1, HIGH);
    digitalWrite(level_2, HIGH);
    digitalWrite(level_3, HIGH);
    digitalWrite(level_4, LOW);
    digitalWrite(level_5, LOW);
  }
  if((volume >= 60) && (volume < 80))
  {
    digitalWrite(level_1, HIGH);
    digitalWrite(level_2, HIGH);
    digitalWrite(level_3, HIGH);
    digitalWrite(level_4, HIGH);
    digitalWrite(level_5, LOW);
  }
  if((volume >= 80))
  {
    digitalWrite(level_1, HIGH);
    digitalWrite(level_2, HIGH);
    digitalWrite(level_3, HIGH);
    digitalWrite(level_4, HIGH);
    digitalWrite(level_5, HIGH);
  }
    
  Serial.print("Analog value= ");
  Serial.println(volume);
  
}
