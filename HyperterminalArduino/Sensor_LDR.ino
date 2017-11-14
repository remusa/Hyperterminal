void fotoresistanceLDR() {
  fotoresistance = analogRead(pinLDR);
  Serial.print("fotoresistance,");
  Serial.println(fotoresistance);

  if (fotoresistance >= 500) {
    Serial.println("color,white");
  } else if (fotoresistance <500) {
    Serial.println("color,black");
  }

  /*
  if (fotoresistance >= colorWhiteMIN && fotoresistance <= colorWhiteMAX) {
    Serial.println("color,white");
  } else if (fotoresistance >= colorBlackMIN && fotoresistance <= colorBlackMAX) {
    Serial.println("color,black");
  } else if (fotoresistance >= colorBlueMIN && fotoresistance <= colorBlueMAX) {
    Serial.println("color,yellow");
  } else if (fotoresistance >= colorRedMIN && fotoresistance <= colorRedMAX) {
    Serial.println("color,blue");
  } else if (fotoresistance >= colorYellowMIN && fotoresistance <= colorYellowMAX) {
    Serial.println("color,red");
  }*/
  
}
