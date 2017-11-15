void getSensors() {
  if (i >= 500) {
    /*motionPIR();
    temperatureLM35();
    temperatureNTC();*/
    fotoresistanceLDR();
    i = 0;
  }
  i++;

  if (j >= 1500) {
    switch (menu) {
      case 1:
        menuLM35();
        break;
      case 2:
        menuNTC();
        break;
      case 3:
        menuPIR();
        break;
      case 4:
        menuLDR();
        break;
    }
    j = 0;
  }
  j++;
}

