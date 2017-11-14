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

  printLM35();
}

void printLM35() {
  Serial.print("temp_LM35");
  Serial.print(",");
  Serial.print((int) LM35_temp);
  Serial.println();
}

