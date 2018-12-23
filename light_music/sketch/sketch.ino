const int analogInPin  = A0;
int sensorAnalogValue  = 0;
const int digitalInPin = 2;
int sensorDigitalValue = 0;
const int quet    = 3;
const int medium  = 5;
const int loud = 7;
 
  
  
void setup() 
{
  Serial.begin(9600);
  Serial.println("Microphone Test" );
}

void loop() 
{
  sensorAnalogValue  = analogRead(analogInPin);
  sensorDigitalValue = digitalRead(digitalInPin);
  
  if(sensorAnalogValue < 500)
  {
    digitalWrite(quet, HIGH);
    digitalWrite(medium, LOW);
    digitalWrite(loud, LOW);
  }
  if((sensorAnalogValue >= 500) && (sensorAnalogValue <= 510))
  {
    digitalWrite(quet, HIGH);
    digitalWrite(medium, HIGH);
    digitalWrite(loud, LOW);
  }
  if(sensorAnalogValue > 510)
  {
    digitalWrite(quet, HIGH);
    digitalWrite(medium, HIGH);
    digitalWrite(loud, HIGH);
  }
  
    
  Serial.print("Analog value= ");
  Serial.print(sensorAnalogValue);
  Serial.print("  Digital value= ");
  Serial.println(sensorDigitalValue);
  delay(100);
}
