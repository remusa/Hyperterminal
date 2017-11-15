void fotoresistanceLDR() {
  fotoresistance = analogRead(pinLDR);

  //ilum = ((long)(1024-V)*A*10)/((long)B*Rc*V);  //usar si LDR entre GND y A0
  //ilum = ((long) fotoresistance * A * 10) / ((long) B * Rc * (1024 - fotoresistance)) / 10; //usar si LDR entre A0 y Vcc (como en el esquema anterior)
  
  Serial.print("fotoresistance,");
  Serial.println(fotoresistance);

  // Perform the analog to digital conversion
  ldrRawData = fotoresistance;
  // RESISTOR VOLTAGE_CONVERSION
  // Convert the raw digital data back to the voltage that was measured on the analog pin
  resistorVoltage = (float) ldrRawData / MAX_ADC_READING * ADC_REF_VOLTAGE;
  // voltage across the LDR is the 5V supply minus the 5k resistor voltage
  ldrVoltage = ADC_REF_VOLTAGE - resistorVoltage;

  // LDR_RESISTANCE_CONVERSION
  // resistance that the LDR would have for that voltage
  ldrResistance = ldrVoltage / resistorVoltage * REF_RESISTANCE;

  // LDR_LUX
  // Change the code below to the proper conversion from ldrResistance to
  // ldrLux
  ldrLux = LUX_CALC_SCALAR * pow(ldrResistance, LUX_CALC_EXPONENT);

  // print out the results
  /*Serial.print("LDR Raw Data   : "); Serial.println(ldrRawData);
  Serial.print("LDR Voltage    : "); Serial.print(ldrVoltage); Serial.println(" volts");
  Serial.print("LDR Resistance : "); Serial.print(ldrResistance); Serial.println(" Ohms");
  Serial.print("LDR Illuminance: "); Serial.print(ldrLux); Serial.println(" lux");*/
  
  Serial.print("luxes,");
  Serial.println((int) ldrLux);

  /*if (fotoresistance >= 500) {
    //Serial.println("color,white");
    color = "white";
    } else if (fotoresistance < 500) {
    //Serial.println("color,black");
    color = "black";
    }*/

  if (fotoresistance >= colorWhiteMIN && fotoresistance <= colorWhiteMAX) {
    Serial.println("color,white");
    color = "white";
  } else if (fotoresistance >= colorBlackMIN && fotoresistance <= colorBlackMAX) {
    Serial.println("color,black");
    color = "black";
  } else if (fotoresistance >= colorBlueMIN && fotoresistance <= colorBlueMAX) {
    Serial.println("color,blue");
    color = "blue";
  } else if (fotoresistance >= colorRedMIN && fotoresistance <= colorRedMAX) {
    Serial.println("color,red");
    color = "red";
  } else if (fotoresistance >= colorYellowMIN && fotoresistance <= colorYellowMAX) {
    Serial.println("color,yellow");
    color = "yellow";
  } else {
    Serial.println("color,error");
    color = "error";
  }

}
