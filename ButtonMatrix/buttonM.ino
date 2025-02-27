#define FIRST_ROW 8
#define SECOND_ROW 9
#define THIRD_ROW 10
#define FIRST_COL 2
#define SECOND_COL 3
#define THIRD_COL 4

int rowConditions[3][3] = {
  {0, 1, 1},
  {1, 0, 1},
  {1, 1, 0}
};

void setup() {
  pinMode(FIRST_COL, INPUT_PULLUP);
  pinMode(SECOND_COL, INPUT_PULLUP);
  pinMode(THIRD_COL, INPUT_PULLUP);
  pinMode(FIRST_ROW, OUTPUT);
  pinMode(SECOND_ROW, OUTPUT);
  pinMode(THIRD_ROW, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int buttonStates[9] = {0};

  for (int i = 0; i < 3; i++) {
    digitalWrite(FIRST_ROW, rowConditions[i][0]);
    digitalWrite(SECOND_ROW, rowConditions[i][1]);
    digitalWrite(THIRD_ROW, rowConditions[i][2]);

    for (int button = 0; button < 9; button++) {
      int rowPin = (button < 3) ? FIRST_ROW : (button < 6) ? SECOND_ROW : THIRD_ROW;
      int colPin = (button % 3 == 0) ? FIRST_COL : (button % 3 == 1) ? SECOND_COL : THIRD_COL;

      int rowState = digitalRead(rowPin);
      int colState = digitalRead(colPin);

      if (rowState == 0 && colState == 0) {
        buttonStates[button] = 1;
      }
    }

    delay(10);
  }

  bool wasButtonPressed = false;

  for (int i = 0; i < 9; i++) {
    if (buttonStates[i] == 1) {
      if (!wasButtonPressed){
        Serial.print("Pressed button(s): ");
        wasButtonPressed = true;
      }
      Serial.print(i + 1);
      Serial.print(" ");
    }
  }

  if (wasButtonPressed){
    Serial.println();
  }

  delay(100);
}
