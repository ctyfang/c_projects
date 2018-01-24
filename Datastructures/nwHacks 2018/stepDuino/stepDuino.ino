#define STEP 10
#define DIR 11

void setup() {
  // put your setup code here, to run once:
  pinMode(STEP ,OUTPUT);
  pinMode(DIR, OUTPUT);
  digitalWrite(DIR, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i;

  for(i=0; i<200; i++){
    digitalWrite(STEP, HIGH);
    digitalWrite(STEP, LOW);
    delay(10);
  }

  //delay(1000);
}
