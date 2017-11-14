//LDR (fotoresistance)
#define pinLDR    A10
int fotoresistance;
int i;

void setup() {
  Serial.begin(9600);
  i = 0;
  
  fotoresistance = 0;
}

void loop() {
  if (i >= 1000) {
    fotoresistanceLDR();
    i = 0;
  }
  i++;  
}

void fotoresistanceLDR() {
  fotoresistance = analogRead(pinLDR);
  Serial.print("fotoresistance = ");
  Serial.println(fotoresistance);

  if (fotoresistance >= 890 && fotoresistance <= 900) {           //895 - 905
    Serial.print("fotoresistance,yellow");
  } else if (fotoresistance >= 910 && fotoresistance <= 920) {    //935 - 945
    Serial.print("fotoresistance,red");
  } else if (fotoresistance >= 921 && fotoresistance <= 925) {    //970 - 980
    Serial.print("fotoresistance,blue");
  } else {
    //Serial.println("fotoresistance,error");
  }
}
