#define DATA_PIN 9
#define DATA_LEVEL LOW
#define SPACE_LEVEL HIGH

#define TU 100
#define DASH_DURATION 3
#define DOT_DURATION 1


String CODES[]={".-","--.."};
char LETTERS[]={'A','Z'};
int NLETTERS=2;

void setup() {
  Serial.begin(9600);
  pinMode (DATA_PIN, OUTPUT);
  digitalWrite(DATA_PIN, SPACE_LEVEL);
}

void loop() {
 if (Serial.available()>=1){
   char letter =Serial.read();
   for (int iletter; iletter <NLETTERS; iletter++){
     if (letter == LETTERS[iletter]){
       String code = CODES[iletter];
       send_letter(code);
     }
   }
 }
}

void send_letter(String code){
      int code_len=code.length();
       for (int i=0; i<code_len; i++){
         char symbol=code[i];
         if (symbol == '.'){
           digitalWrite(DATA_PIN, DATA_LEVEL);
           delay(TU);
         }
         if (symbol == '-'){
           digitalWrite(DATA_PIN, DATA_LEVEL);
           delay(DASH_DURATION*TU);
         }
          digitalWrite(DATA_PIN, SPACE_LEVEL);
           delay(TU);
         }
       delay((DASH_DURATION-1)*TU);
}
