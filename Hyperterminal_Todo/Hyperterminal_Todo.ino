#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif

#include <Adafruit_GFX.h>
#include <TouchScreen.h>

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

#define TS_MINX 120
#define TS_MAXX 900
#define TS_MINY 70
#define TS_MAXY 920

//SPI Communication
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4

//Color Definitons
#define BLACK     0x0000
#define BLUE      0x001F
#define GREY      0xCE79
#define LIGHTGREY 0xDEDB
#define MINPRESSURE 1
#define MAXPRESSURE 1000

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
// Pins A2-A6
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 364);

//Size of key containers 70px
#define BOXSIZE 70

//2.4 = 240 x 320
//Height 319 to fit on screen

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
//Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

//Container variables for touch coordinates
int X, Y, Z;

//Screen height without hidden pixel
double tHeight = tft.height() - 1;
//Centering the mid square
double center = (tft.width() / 2) - (BOXSIZE / 2);
//Space between squares
double padding = 10;
//Position of squares to the left and right of center
double fromCenter = BOXSIZE + padding;
//Second row Y-Axis position
double secondRow = BOXSIZE + padding;
//Third row Y-Axis position
double thirdRow = secondRow + BOXSIZE + padding;
//Fourth row Y-Axis position
double fourthRow = thirdRow + BOXSIZE + padding;
//Y-Axis align for all squares
double verticalAlign = (tHeight - ((BOXSIZE * 4) + (padding * 3))) / 2;
//Left column starting x posision
double leftColPositionX = center - fromCenter;
//Mid column starting x posision
double midColPositionX = center;
//Right column starting x posision
double rightColPositionX = center + fromCenter;

///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

//EEPROM
#include <EEPROM.h>

//LM35
#define pinLM35   A8

//NTC
#define pinNTC    A9
#define R1        10e3
#define R0        10e3 // resistencia de 10k

#define T0_EEPROM  0    //EEPROM address
#define B_EEPROM   1

uint16_t i;
uint16_t T0;          //temperatura ambiente
uint16_t B;           //constante de calibración
String numberEntered;

void setup() {
  Serial.begin(9600);

  i = 0;
  T0 = EEPROM.read(T0_EEPROM);  //temperatura ambiente
  B = 20;   //constante de calibración

  //EEPROM.write(ADDRESS,VALUE);
  //EEPROM.update(T0_EEPROM, T0);
  EEPROM.update(B_EEPROM, B);

  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  //Background color
  tft.fillScreen(LIGHTGREY);
  //Colors
  createButtons();
  insertNumbers();
  Serial.println(F("Presiona una tecla: "));
}

void loop() {
  if (i >= 500) {
    temperatureLM35();
    temperatureNTC();
    calibrateNTC();
    i = 0;
  }
  i++;

  runKeypad();
}

void calibrateNTC() {
  if (Serial.available() > 0) {
    uint16_t T0_read = Serial.parseInt();

    Serial.print("T0_read,");
    Serial.print(T0_read);
    Serial.println("");

    if (T0_read <= 155 && T0_read >= -55) {
      T0 = T0_read;
      Serial.print("calibrateNTC,");
      Serial.print(T0);
      Serial.println("");
    }
  }
}

void temperatureLM35() {
  float volt, res, temp;

  volt = analogRead(pinLM35);
  res = (volt / 1024.0) * 500;
  temp = (volt * 500) / 10230;

  Serial.print("temp_LM35");
  Serial.print(",");
  Serial.print((int) temp);
  Serial.println();
}

void temperatureNTC() {
  float volts, T, RT, AT = 0, R;
  T0 = EEPROM.read(T0_EEPROM);
  B = EEPROM.read(B_EEPROM);

  volts = analogRead(pinNTC) * 0.0048828125;
  RT = R1 * volts / (5 - volts);
  T = T0 - B * log(RT / R0); //si rt es menor a r0 la temperatura sube, resultado negativo
  R = R0 * (log(B * ((1 / T) - (1 / T0))));

  Serial.print("temp_NTC");
  Serial.print(",");
  Serial.print((int)(T));
  Serial.println();
  Serial.print("res_NTC");
  Serial.print(",");
  Serial.print((int) R);
  Serial.println();
}

void runKeypad() {
  retrieveTouch();
  int boxHeightRow1 = verticalAlign + BOXSIZE;
  int boxHeightRow2 = secondRow + BOXSIZE;
  int boxHeightRow3 = thirdRow + BOXSIZE;
  int boxHeightRow4 = fourthRow + BOXSIZE;

  if (Z > MINPRESSURE && Z < MAXPRESSURE) {
    //Check if element clicked is in left column
    if (X > leftColPositionX && X < (leftColPositionX + BOXSIZE)) {
      //Check if element clicked is in row 1
      if (Y > verticalAlign) {
        if (Y < boxHeightRow1) {
          Serial.println("key,1");
          numberEntered = numberEntered + "1";
          delay(150);
        }
        //Check if element clicked is in row 2
        else if (Y < boxHeightRow2) {
          Serial.println("key,4");
          numberEntered = numberEntered + "4";
          delay(150);
        }
        //Check if element clicked is in row 3
        else if (Y < boxHeightRow3) {
          Serial.println("key,7");
          numberEntered = numberEntered + "7";
          delay(150);
        }
        //Check if element clicked is in row 4
        else if (Y < boxHeightRow4) {
          Serial.println("key,0");
          numberEntered = numberEntered + "0";
          delay(150);
        }
      }
      //Check if element clicked is in mid column
    } else if (X > midColPositionX && X < (midColPositionX + BOXSIZE)) {
      //Check if element clicked is in row 1
      if (Y > verticalAlign) {
        if (Y < boxHeightRow1) {
          Serial.println("key,2");
          numberEntered = numberEntered + "2";
          delay(150);
        }
        //Check if element clicked is in row 2
        else if (Y < boxHeightRow2) {
          Serial.println("key,5");
          numberEntered = numberEntered + "5";
          delay(150);
        }
        //Check if element clicked is in row 3
        else if (Y < boxHeightRow3) {
          Serial.println("key,8");
          numberEntered = numberEntered + "8";
          delay(150);
        }
        //Check if element clicked is in row 4
        else if (Y < boxHeightRow4) {
          Serial.println("key,0");
          numberEntered = numberEntered + "0";
          delay(150);
        }
      }
      //Check if element clicked is in third column
    } else if (X > rightColPositionX && X < (rightColPositionX + BOXSIZE)) {
      if (Y > verticalAlign) {
        //Check if element clicked is in row 1
        if (Y < boxHeightRow1) {
          Serial.println("key,3");
          numberEntered = numberEntered + "3";
          delay(150);
        }
        //Check if element clicked is in row 2
        else if (Y < boxHeightRow2) {
          Serial.println("key,6");
          numberEntered = numberEntered + "6";
          delay(150);
        }
        //Check if element clicked is in row 3
        else if (Y < boxHeightRow3) {
          //Serial.println("key,9");
          numberEntered = numberEntered + "9";
          delay(150);
        }
        //Check if element clicked is in row 3
        else if (Y < boxHeightRow4) {
          //Serial.println("key,.");

          if (numberEntered == "") {
            EEPROM.update(T0_EEPROM, 11);
          } else {
            T0 = numberEntered.toInt();
            if (T0 <= 155) {
              EEPROM.update(T0_EEPROM, T0);
              Serial.print("numberEntered,");
              Serial.print(T0);
              Serial.println("");
              numberEntered = "";
            } else {
              Serial.print("numberEntered,error");
              Serial.println("");
              numberEntered = "";
            }
          }
          delay(150);
        }
      }
    }
  }
}

void retrieveTouch() {
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  //If sharing pins, you'll need to fix the directions of the touchscreen pins
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  //Scale from 0->1023 to tft.width
  X = map(p.x, TS_MAXX, TS_MINX, 0, tft.width());
  Y = map(p.y, TS_MAXY, TS_MINY, 0, tft.height());
  Z = p.z;
}

void createButtons() {
  //(initial x,initial y,width,height,color)
  double secondRowVertialAlign = secondRow + verticalAlign;
  double thirdRowVertialAlign = thirdRow + verticalAlign;
  double fourthRowVertialAlign = fourthRow + verticalAlign;

  /***Draw filled squares with specified dimensions and position***/
  //First Row
  tft.fillRect(leftColPositionX, verticalAlign, BOXSIZE, BOXSIZE, GREY);
  tft.fillRect(midColPositionX, verticalAlign, BOXSIZE, BOXSIZE, GREY);
  tft.fillRect(rightColPositionX, verticalAlign, BOXSIZE, BOXSIZE, GREY);

  //Second Row
  tft.fillRect(leftColPositionX, secondRowVertialAlign, BOXSIZE, BOXSIZE, GREY);
  tft.fillRect(midColPositionX, secondRowVertialAlign, BOXSIZE, BOXSIZE, GREY);
  tft.fillRect(rightColPositionX, secondRowVertialAlign, BOXSIZE, BOXSIZE, GREY);

  //Third Row
  tft.fillRect(leftColPositionX, thirdRowVertialAlign, BOXSIZE, BOXSIZE, GREY);
  tft.fillRect(midColPositionX, thirdRowVertialAlign, BOXSIZE, BOXSIZE, GREY);
  tft.fillRect(rightColPositionX, thirdRowVertialAlign, BOXSIZE, BOXSIZE, GREY);

  //Fourth Row
  tft.fillRect(leftColPositionX, fourthRowVertialAlign, (BOXSIZE * 2) + padding, BOXSIZE, GREY);
  tft.fillRect(rightColPositionX, fourthRowVertialAlign, BOXSIZE, BOXSIZE, GREY);

  /***Draw Borders around squares***/
  //First Row
  tft.drawRect(leftColPositionX, verticalAlign, BOXSIZE, BOXSIZE, BLACK);
  tft.drawRect(midColPositionX, verticalAlign, BOXSIZE, BOXSIZE, BLACK);
  tft.drawRect(rightColPositionX, verticalAlign, BOXSIZE, BOXSIZE, BLACK);

  //Second Row
  tft.drawRect(leftColPositionX, secondRowVertialAlign, BOXSIZE, BOXSIZE, BLACK);
  tft.drawRect(midColPositionX, secondRowVertialAlign, BOXSIZE, BOXSIZE, BLACK);
  tft.drawRect(rightColPositionX, secondRowVertialAlign, BOXSIZE, BOXSIZE, BLACK);

  //Third Row
  tft.drawRect(leftColPositionX, thirdRowVertialAlign, BOXSIZE, BOXSIZE, BLACK);
  tft.drawRect(midColPositionX, thirdRowVertialAlign, BOXSIZE, BOXSIZE, BLACK);
  tft.drawRect(rightColPositionX, thirdRowVertialAlign, BOXSIZE, BOXSIZE, BLACK);

  //Fourth Row
  tft.drawRect(leftColPositionX, fourthRowVertialAlign, (BOXSIZE * 2) + padding, BOXSIZE, BLACK);
  tft.drawRect(rightColPositionX, fourthRowVertialAlign, BOXSIZE, BOXSIZE, BLACK);
}

void insertNumbers() {
  //Centers text horizontally on all three columns
  double leftColCursorX   = leftColPositionX + (BOXSIZE / 3);
  double midColCursorX    = midColPositionX  + (BOXSIZE / 3);
  double rightColCursorX  = rightColPositionX + (BOXSIZE / 3);
  //Centers text horizontally on all four rows
  double firstRowCursorY  = verticalAlign + (BOXSIZE / 3);
  double secondRowCursorY = secondRow + firstRowCursorY;
  double thirdRowCursorY  = thirdRow  + firstRowCursorY;
  double fourthRowCursorY = fourthRow + firstRowCursorY;

  tft.setTextSize(4);
  tft.setTextColor(BLACK);

  //Insert Number 1
  tft.setCursor(leftColCursorX, firstRowCursorY);
  tft.println("1");

  //Insert Number 2
  tft.setCursor(midColCursorX, firstRowCursorY);
  tft.println("2");

  //Insert Number 3
  tft.setCursor(rightColCursorX, firstRowCursorY);
  tft.println("3");

  //Insert Number 4
  tft.setCursor(leftColCursorX, secondRowCursorY);
  tft.println("4");

  //Insert Number 5
  tft.setCursor(midColCursorX, secondRowCursorY);
  tft.println("5");

  //Insert Number 6
  tft.setCursor(rightColCursorX, secondRowCursorY);
  tft.println("6");

  //Insert Number 7
  tft.setCursor(leftColCursorX, thirdRowCursorY);
  tft.println("7");

  //Insert Number 8
  tft.setCursor(midColCursorX, thirdRowCursorY);
  tft.println("8");

  //Insert Number 9
  tft.setCursor(rightColCursorX, thirdRowCursorY);
  tft.println("9");

  //Insert Number 0
  tft.setCursor(leftColPositionX + BOXSIZE, fourthRowCursorY);
  tft.println("0");

  //Insert Period Character
  //tft.setCursor(rightColCursorX, fourthRowCursorY);
  //tft.println(".");

  //Enter
  tft.setCursor(rightColCursorX, fourthRowCursorY);
  tft.println("->");
}
