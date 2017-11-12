//PIR (Motion)
#define pinPIR    30
int motionPIRstate;

void setup() {
  Serial.begin(9600);

  //PIR
  motionPIRstate = 0;
  pinMode(pinPIR, INPUT);     // declare sensor as input
}

void loop() {
  motionPIR();
}

void motionPIR() {
  motionPIRstate = digitalRead(pinPIR);

  if (motionPIRstate == HIGH) {
    Serial.println("motionPIR,1");
  } else {
    Serial.println("motionPIR,0");
  }
}

