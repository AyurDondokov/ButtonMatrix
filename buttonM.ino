
#define FIRST_ROW 8   
#define SECOND_ROW 9  
#define FIRST_COL 10  
#define SECOND_COL 11 

int rowConditions[2][2] = { {0, 1}, {1, 0} };

void setup() {
 
  pinMode(FIRST_COL, INPUT_PULLUP);   
  pinMode(SECOND_COL, INPUT_PULLUP);
  pinMode(FIRST_ROW, OUTPUT);         
  pinMode(SECOND_ROW, OUTPUT);

  
  Serial.begin(9600);
}

void loop() {
  int buttonStates[4] = {0, 0, 0, 0}; 

  
  for (int i = 0; i < 2; i++) {
    
    digitalWrite(FIRST_ROW, rowConditions[i][0]);
    digitalWrite(SECOND_ROW, rowConditions[i][1]);

    
    for (int button = 0; button < 4; button++) {
      
      int rowPin = (button < 2) ? FIRST_ROW : SECOND_ROW;
      int colPin = (button % 2 == 0) ? FIRST_COL : SECOND_COL;

      
      int rowState = digitalRead(rowPin);
      int colState = digitalRead(colPin);

      
      if (rowState == 0 && colState == 0) {
        buttonStates[button] = 1;
      }
    }

    delay(10); 
  }

  bool wasButtonPressed = false; 

  for (int i = 0; i < 4; i++) {
    if (buttonStates[i] == 1) { 
      if (!wasButtonPressed) {  
        Serial.print("Pressed button(s): ");
        wasButtonPressed = true;
      }
      Serial.print(i + 1); 
      Serial.print(" ");
    }
  }

  if (wasButtonPressed) {
    Serial.println(); 
  }

  delay(100); 
}