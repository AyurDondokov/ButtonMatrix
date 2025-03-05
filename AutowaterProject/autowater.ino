const int soilMoisturePin = A0;
const int ledPin = 2;        
const int pumpPin = 4;        
const int thresholdPin = A1;  
const int debounceDelay = 2000;

bool isPumping = false;
unsigned long lastChangeTime = 0;

void setup() {
  pinMode(ledPin, OUTPUT);    
  pinMode(pumpPin, OUTPUT);   
  Serial.begin(9600);         
}

void loop() {
  int soilMoistureValue = analogRead(soilMoisturePin); 
  int thresholdValue = analogRead(thresholdPin);       
  
  int normalizedSoilMoisture = map(soilMoistureValue, 0, 876, 0, 100);
  int normalizedThreshold = map(thresholdValue, 0, 1023, 0, 100);

  Serial.print("Soil Moisture: ");
  Serial.print(normalizedSoilMoisture);
  Serial.print(", Threshold: ");
  Serial.println(normalizedThreshold);

  unsigned long currentTime = millis();

  if ((currentTime - lastChangeTime) > debounceDelay) {
    if (normalizedSoilMoisture < normalizedThreshold && !isPumping) {
      digitalWrite(ledPin, HIGH);
      digitalWrite(pumpPin, HIGH);
      isPumping = true;
      lastChangeTime = currentTime;
    } else if (normalizedSoilMoisture >= normalizedThreshold && isPumping) {
      digitalWrite(ledPin, LOW);
      digitalWrite(pumpPin, LOW);
      isPumping = false;
      lastChangeTime = currentTime;
    }
  }

  delay(500);
}
