void temperatureNTC() {
  NTC_volts = analogRead(pinNTC) * 0.0048828125;
  NTC_RT = NTC_R1 * NTC_volts / (5 - NTC_volts);
  NTC_T = NTC_T0 - NTC_B * log(NTC_RT / NTC_R0); //si rt es menor a r0 la temperatura sube, resultado negativo
  NTC_R = NTC_R0 * (log(NTC_B * ((1 / NTC_T) - (1 / NTC_T0))));

  printNTC();
}

void printNTC() {
  Serial.print("temp_NTC");
  Serial.print(",");
  Serial.print((int)(NTC_T));
  Serial.println();
  Serial.print("res_NTC");
  Serial.print(",");
  Serial.print((int) NTC_R);
  Serial.println();
}

