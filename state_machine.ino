
#define DIR_1        4 
#define SPEED_1      5 
#define SPEED_2      6 
#define DIR_2        7 

#define LEFT_SIDE_ECHO 8
#define LEFT_SIDE_TRIGGER 9
#define FRONT_SIDE_ECHO 11
#define FRONT_SIDE_TRIGGER 12

const int LD = 23; 
const int FD = 23; 
const int CD = 16; 

int ld = 0; 
int fd = 0;
int prev_ld = 0;
int counter = 0;
bool isRotating = false;
long lastTime = millis();
int last_fd = FD * 2;

void move(int rightSideSpeed, int leftSideSpeed) {
  digitalWrite(DIR_1, rightSideSpeed <= 0);
  digitalWrite(DIR_2, leftSideSpeed > 0);
  analogWrite(SPEED_1, abs(rightSideSpeed));
  analogWrite(SPEED_2, abs(leftSideSpeed));
}

void stop() {
  move(0, 0);
}

void forward() {
  move(255, 255);
}

void turn_left() {
  move(255, 100);
}

void turn_right() {
  move(100, 255);
}

void rotate_left() {
  move(255, 0);
}

void rotate_right() {
  move(0, 255);
}

void back() {
  move(-255, 255);
}

long get_distance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(5);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return (duration / 2) / 29.1;
}

void setup() {
  Serial.begin(9600);

  for (int i = 4; i <= 7; i++) {
    pinMode(i, OUTPUT);
  }

  pinMode(LEFT_SIDE_ECHO, INPUT);
  pinMode(LEFT_SIDE_TRIGGER, OUTPUT);
  pinMode(FRONT_SIDE_ECHO, INPUT);
  pinMode(FRONT_SIDE_TRIGGER, OUTPUT);
}

enum State { FORWARD, ROTATE_RIGHT, ROTATE_LEFT, TURN_RIGHT, TURN_LEFT, BACK };

State currentState = FORWARD;

void updateState() {
  switch (currentState) {
    case FORWARD:
      if (fd < FD && ld < LD) {
        currentState = ROTATE_RIGHT;
      } else if (ld > LD && fd < FD) {
        currentState = ROTATE_LEFT;
      } else if (ld < CD - 3 && prev_ld < CD) {
        currentState = TURN_RIGHT;
      } else if (ld > CD && prev_ld > CD) {
        currentState = TURN_LEFT;
      } else if (last_fd > FD + 5) {
        currentState = FORWARD;
      } else if (fd <= 5) {
        currentState = BACK;
      }
      break;
    case ROTATE_RIGHT:
      if (!isRotating) {
        rotate_right();
        isRotating = true;
      }
      break;
    case ROTATE_LEFT:
      if (!isRotating) {
        rotate_left();
        isRotating = true;
      }
      break;
    case TURN_RIGHT:
      if (!isRotating) {
        turn_right();
        isRotating = true;
      }
      break;
    case TURN_LEFT:
      if (!isRotating) {
        turn_left();
        isRotating = true;
      }
      break;
    case BACK:
      if (!isRotating) {
        back();
        isRotating = true;
      }
      break;
  }
}

void loop() {
  fd = get_distance(FRONT_SIDE_TRIGGER, FRONT_SIDE_ECHO);
  ld = get_distance(LEFT_SIDE_TRIGGER, LEFT_SIDE_ECHO);

  updateState();

  switch (currentState) {
    case FORWARD:
      forward();
      break;
    case ROTATE_RIGHT:
      rotate_right();
      break;
    case ROTATE_LEFT:
      rotate_left();
      break;
    case TURN_RIGHT:
      turn_right();
      break;
    case TURN_LEFT:
      turn_left();
      break;
    case BACK:
      back();
      break;
  }

  if (millis() - lastTime > 500) {
    prev_ld = ld;
    last_fd = fd;
    lastTime = millis();
    isRotating = false;
  }

  Serial.print("Current state: ");
  Serial.println(currentState);
  Serial.print("Current fd & ld: ");
  Serial.print(fd);
  Serial.print(" ");
  Serial.println(ld);
}