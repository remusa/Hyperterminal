int ledPin0 = 40;
int ledPin1 = 41;
int ledPin2 = 42;

void setup() {
  Serial.begin(9600);

  pinMode(ledPin0, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  digitalWrite(ledPin0, LOW);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
}

void loop() {
  digitalWrite(ledPin0, HIGH);
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);

  delay(1000);

  digitalWrite(ledPin0, LOW);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);

  delay(1000);
}
