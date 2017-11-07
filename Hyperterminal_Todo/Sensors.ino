void getSensors() {
  if (i >= 500) {
    temperatureLM35();
    temperatureNTC();
    printValues();
    i = 0;
  }
  i++;
}

void printValues() {
  //LM35
  Serial.print("temp_LM35");
  Serial.print(",");
  Serial.print((int) LM35_temp);
  Serial.println();

  //NTC
  Serial.print("temp_NTC");
  Serial.print(",");
  Serial.print((int)(NTC_T));
  Serial.println();
  Serial.print("res_NTC");
  Serial.print(",");
  Serial.print((int) NTC_R);
  Serial.println();
}

void temperatureLM35() {
  /*LM35_volt = analogRead(pinLM35);
    LM35_res = (LM35_volt / 1024.0) * 500;
    LM35_temp = (LM35_volt * 500) / 10230;*/

  /*LM35_volt = analogRead(pinLM35) * 2;
    LM35_res = (5 * LM35_volt * 100.0) / 1024.0;
    LM35_temp = LM35_res / 10;*/

  /*LM35_volt = analogRead(pinLM35);
    LM35_volt = (LM35_volt * 500) / 1024;
    LM35_temp = LM35_volt / 10;*/

  LM35_volt = analogRead(pinLM35);
  //LM35_volt = (LM35_volt * 500) / 1024;
  LM35_temp = LM35_volt / 9.31; //10
}

void temperatureNTC() {
  //NTC_T0 = EEPROM.read(T0_EEPROM);
  //NTC_B = EEPROM.read(B_EEPROM);

  NTC_volts = analogRead(pinNTC) * 0.0048828125;
  NTC_RT = NTC_R1 * NTC_volts / (5 - NTC_volts);
  NTC_T = NTC_T0 - NTC_B * log(NTC_RT / NTC_R0); //si rt es menor a r0 la temperatura sube, resultado negativo
  NTC_R = NTC_R0 * (log(NTC_B * ((1 / NTC_T) - (1 / NTC_T0))));
}
