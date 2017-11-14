void getSensors() {
  if (i >= 500) {
    temperatureLM35();
    temperatureNTC();
    fotoresistanceLDR();
    motionPIR();
    i = 0;
  }
  i++;
}

