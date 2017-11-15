uint16_t x0 = 40;
uint16_t y0 = 60;
uint16_t w = 125;
uint16_t h = 30;
uint16_t xText = 85;
uint16_t yText = 68;
uint16_t ySpace = 40;

void menuMain() {
  menu = 0;

  //TITLE
  tft.fillScreen(WHITE);
  tft.setCursor(40, 10);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("SISTEMAS PROGRAMABLES");

  //CREDITS
  tft.setCursor(40, 30);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.print("por RMS");

  //BUTTON 1 - LM35
  tft.fillRect(x0, y0, w, h, RED); //x0, y0, w, h, color
  tft.drawRect(x0, y0, w, h, BLACK);
  tft.setCursor(xText, yText);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("LM35");

  //BUTTON 2 - NTC
  tft.fillRect(x0, y0 + (ySpace * 1), w, h, RED); //x0, y0, w, h, color
  tft.drawRect(x0, y0 + (ySpace * 1), w, h, BLACK);
  tft.setCursor(xText, yText + (ySpace * 1));
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("NTC");

  //BUTTON 3 - PIR
  tft.fillRect(x0, y0 + (ySpace * 2), w, h, RED); //x0, y0, w, h, color
  tft.drawRect(x0, y0 + (ySpace * 2), w, h, BLACK);
  tft.setCursor(xText, yText + (ySpace * 2));
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("PIR");

  //BUTTON 4 - LDR
  tft.fillRect(x0, y0 + (ySpace * 3), w, h, RED); //x0, y0, w, h, color
  tft.drawRect(x0, y0 + (ySpace * 3), w, h, BLACK);
  tft.setCursor(xText, yText + (ySpace * 3));
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("LDR");
}

void menuLM35() {
  menu = 1;

  //TITLE
  tft.fillScreen(WHITE);
  tft.setCursor(60, 10);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.print("Sensor 1: LM35");

  //VALUES
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.setCursor(20, 40);
  tft.print("V: ");
  tft.setCursor(50, 40);
  tft.print(LM35_volt);
  tft.setCursor(20, 60);
  tft.print("T: ");
  tft.setCursor(50, 60);
  tft.print(LM35_temp);
  tft.setCursor(20, 80);

  //BUTTON RELOAD
  /*tft.fillRect(x0, y0 + (ySpace * 1.5), w, h, RED); //x0, y0, w, h, color
    tft.drawRect(x0, y0 + (ySpace * 1.5), w, h, BLACK);
    tft.setCursor(xText, yText + (ySpace * 1.5));
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("RELOAD");*/

  //BUTTON MAIN MENU
  tft.fillRect(x0 * 2.5, y0 + (ySpace * 3.5), w, h, RED); //x0, y0, w, h, color
  tft.drawRect(x0 * 2.5, y0 + (ySpace * 3.5), w, h, BLACK);
  tft.setCursor(xText * 1.6, yText + (ySpace * 3.5));
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("MENU");
}

void menuNTC() {
  menu = 2;

  //TITLE
  tft.fillScreen(WHITE);
  tft.setCursor(60, 10);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.print("Sensor 2: NTC");

  //VALUES
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.setCursor(20, 40);
  tft.print("T: ");
  tft.setCursor(50, 40);
  tft.print(NTC_T);
  tft.setCursor(20, 60);
  tft.print("R: ");
  tft.setCursor(50, 60);
  tft.print(NTC_R);
  tft.setCursor(20, 80);
  tft.print("T0: ");
  tft.setCursor(50, 80);
  tft.print(NTC_T0);
  tft.setCursor(20, 100);
  tft.print("B: ");
  tft.setCursor(50, 100);
  tft.print(NTC_B);

  //BUTTON CALIBRATE T0
  tft.fillRect(200, 30, 40, 30, RED); //x0, y0, w, h, color
  tft.drawRect(200, 30, 40, 30, BLACK);
  tft.setCursor(207, 37);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("T0");

  //BUTTON CALIBRATE B
  tft.fillRect(200, 65, 40, 30, RED); //x0, y0, w, h, color
  tft.drawRect(200, 65, 40, 30, BLACK);
  tft.setCursor(210, 72);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("B");

  //BUTTON MAIN MENU
  tft.fillRect(x0 * 2.5, y0 + (ySpace * 3.5), w, h, RED); //x0, y0, w, h, color
  tft.drawRect(x0 * 2.5, y0 + (ySpace * 3.5), w, h, BLACK);
  tft.setCursor(xText * 1.6, yText + (ySpace * 3.5));
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("MENU");
}

void menuPIR() {
  menu = 3;

  //TITLE
  tft.fillScreen(WHITE);
  tft.setCursor(60, 10);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.print("Sensor 3: PIR");

  //VALUES
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.setCursor(20, 40);
  tft.print("Movimiento: ");
  tft.setCursor(160, 40);
  tft.print(motionPIRstate);

  //BUTTON MAIN MENU
  tft.fillRect(x0 * 2.5, y0 + (ySpace * 3.5), w, h, RED); //x0, y0, w, h, color
  tft.drawRect(x0 * 2.5, y0 + (ySpace * 3.5), w, h, BLACK);
  tft.setCursor(xText * 1.6, yText + (ySpace * 3.5));
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("MENU");
}

void menuLDR() {
  menu = 4;

  //TITLE
  tft.fillScreen(WHITE);
  tft.setCursor(60, 10);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.print("Sensor 4: LDR");

  //VALUES
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.setCursor(20, 40);
  tft.print("Lumenes: ");
  tft.setCursor(120, 40);
  tft.print(fotoresistance);
  tft.setCursor(20, 60);
  tft.print("Luxes: ");
  tft.setCursor(120, 60);
  tft.print(ldrLux);
  tft.setCursor(20, 80);
  tft.print("Color: ");

  if (color == "white") {
    tft.fillRect(x0 * 3.3, y0 + (ySpace * 1), 50, 50, WHITE); //x0, y0, w, h, color
    tft.drawRect(x0 * 3.3, y0 + (ySpace * 1), 50, 50, BLACK);
  } else if (color == "black") {
    tft.fillRect(x0 * 3.3, y0 + (ySpace * 1), 50, 50, BLACK); //x0, y0, w, h, color
    tft.drawRect(x0 * 3.3, y0 + (ySpace * 1), 50, 50, BLACK);
  } else if (color == "blue") {
    tft.fillRect(x0 * 3.3, y0 + (ySpace * 1), 50, 50, BLUE); //x0, y0, w, h, color
    tft.drawRect(x0 * 3.3, y0 + (ySpace * 1), 50, 50, BLACK);
  } else if (color == "red") {
    tft.fillRect(x0 * 3.3, y0 + (ySpace * 1), 50, 50, RED); //x0, y0, w, h, color
    tft.drawRect(x0 * 3.3, y0 + (ySpace * 1), 50, 50, BLACK);
  } else if (color == "yellow") {
    tft.fillRect(x0 * 3.3, y0 + (ySpace * 1), 50, 50, YELLOW); //x0, y0, w, h, color
    tft.drawRect(x0 * 3.3, y0 + (ySpace * 1), 50, 50, BLACK);
  }

  //BUTTON CALIBRATE R
  tft.fillRect(200, 30, 40, 30, RED); //x0, y0, w, h, color
  tft.drawRect(200, 30, 40, 30, BLACK);
  tft.setCursor(207, 37);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("R");

  //BUTTON MAIN MENU
  tft.fillRect(x0 * 2.5, y0 + (ySpace * 3.5), w, h, RED); //x0, y0, w, h, color
  tft.drawRect(x0 * 2.5, y0 + (ySpace * 3.5), w, h, BLACK);
  tft.setCursor(xText * 1.6, yText + (ySpace * 3.5));
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("MENU");
}
