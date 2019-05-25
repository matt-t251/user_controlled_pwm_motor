
int SwitchA = 2;           // Pin for switch A.
int SwitchB = 3;           // Pin for switch B.
int LatchC = 4;            // Pin for switch C.
int AState;
int BState;
int CState;
int Aconfig;
int Bconfig;
int Cconfig;
int previousA = 0;
int previousB = 0;
int previousC = 0;
int motorPin = 13;         // Pin with pulse for motor.
int breakPin = 12;         // Pin for disc break.
int varDelay = 1500;       // the current pulse width

void setup() {

  pinMode(SwitchA, INPUT);
  pinMode(SwitchB, INPUT);
  pinMode(LatchC, INPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(breakPin, OUTPUT);
  digitalWrite(motorPin, LOW);
  digitalWrite(breakPin, LOW);
  Serial.begin(9600);
  Serial.println("Setup Finished");
}

void loop() {
  // Debounce and read buttons and save config.
  
  Serial.println("-------------------------");
  
  AState = digitalRead(SwitchA);
  if (AState == HIGH && previousA == 0) {
    Aconfig = HIGH;
    Serial.println("Aconfig HIGH");
  };
  previousA = AState;

  Bconfig = digitalRead(SwitchB);
  if (Bconfig == HIGH) { Serial.println("Bconfig HIGH"); };

  Cconfig = digitalRead(LatchC);
  if (Cconfig == HIGH) { Serial.println("Cconfig HIGH"); };


  if (Cconfig == HIGH) {

    digitalWrite(breakPin, HIGH);
    varDelay = 1500;
    Serial.println("Break set");
    
    // reset
    Aconfig = LOW;
    Bconfig = LOW;
    Cconfig = LOW;

  } else {

    digitalWrite(breakPin, LOW);
    Serial.println("Break released");

    if (Aconfig == HIGH && Bconfig == LOW) {
      varDelay = varDelay + 10;
      Serial.println("Speed increase");
    };

    if (Aconfig == HIGH && Bconfig == HIGH) {
      varDelay = varDelay - 10;
      Serial.println("Speed decrease");
    };
    // reset
    Aconfig = LOW;
    Bconfig = LOW;
    Cconfig = LOW;

  };

  // generate a squrae wave to the spec of varDelay.
  Serial.println(varDelay);
  digitalWrite(motorPin, HIGH);
  delayMicroseconds(varDelay);                                                  
  digitalWrite(motorPin, LOW);
  Serial.println("--------------------");
}
