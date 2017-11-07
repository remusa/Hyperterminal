uint16_t x0 = 50;
uint16_t y0 = 60;
uint16_t w = 210;
uint16_t h = 40;
uint16_t xText = 125;
uint16_t yText = 75;
uint16_t ySpace = 50;

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
  tft.print("R: ");
  tft.setCursor(50, 60);
  tft.print(LM35_res);
  tft.setCursor(20, 80);
  tft.print("T: ");
  tft.setCursor(50, 80);
  tft.print(LM35_temp);

  //BUTTON RELOAD
  tft.fillRect(x0, y0 + (ySpace * 1.5), w, h, RED); //x0, y0, w, h, color
  tft.drawRect(x0, y0 + (ySpace * 1.5), w, h, BLACK);
  tft.setCursor(xText, yText + (ySpace * 1.5));
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("RELOAD");

  //BUTTON MAIN MENU
  tft.fillRect(x0, y0 + (ySpace * 2.5), w, h, RED); //x0, y0, w, h, color
  tft.drawRect(x0, y0 + (ySpace * 2.5), w, h, BLACK);
  tft.setCursor(xText, yText + (ySpace * 2.5));
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

  //BUTTON RELOAD
  tft.fillRect(x0, y0 + (ySpace * 1.5), w, h, RED); //x0, y0, w, h, color
  tft.drawRect(x0, y0 + (ySpace * 1.5), w, h, BLACK);
  tft.setCursor(xText, yText + (ySpace * 1.5));
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("RELOAD");

  //BUTTON MAIN MENU
  tft.fillRect(x0, y0 + (ySpace * 2.5), w, h, RED); //x0, y0, w, h, color
  tft.drawRect(x0, y0 + (ySpace * 2.5), w, h, BLACK);
  tft.setCursor(xText, yText + (ySpace * 2.5));
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.print("MENU");
}

