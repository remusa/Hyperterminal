void getSensors() {
  if (i >= 500) {
    //temperatureLM35();
    //temperatureNTC();
    //motionPIR();
    fotoresistanceLDR();
    i = 0;
  }
  i++;
}

