void motionPIR() {
  motionPIRstate = digitalRead(pinPIR);

  if (motionPIRstate == HIGH) {
    Serial.println("motionPIR,1");
  } else if (motionPIRstate == LOW) {
    Serial.println("motionPIR,0");
  }
}

