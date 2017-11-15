#include <TouchScreen.h>
#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library

#define YP          A3  // must be an analog pin, use "An" notation!
#define XM          A2  // must be an analog pin, use "An" notation!
#define YM          9   // can be a digital pin
#define XP          8   // can be a digital pin

//SPI Communication
#define LCD_CS      A3
#define LCD_CD      A2
#define LCD_WR      A1
#define LCD_RD      A0
#define LCD_RESET   A4  // optional

#define TS_MINX   205
#define TS_MINY   887
#define TS_MAXX   904
#define TS_MAXY   271

//Color Definitons
#define BLACK     0x0000
#define WHITE     0xFFFF
#define GREY      0xCE79
#define LIGHTGREY 0xDEDB
#define BLUE      0x001F
#define RED       0xF800
#define GREEN     0x07E0
#define CYAN      0x07FF
#define MAGENTA   0xF81F
#define YELLOW    0xFFE0

//Pressure
#define MINPRESSURE 10
#define MAXPRESSURE 1000

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
// Pins A2-A6
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); //364

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

//Size of key containers
#define BOXSIZE 40

//2.4 = 240 x 320
//Height 319 to fit on screen

//Screen height without hidden pixel
double tHeight = tft.height() - 1;
//Centering the mid square
double center = (tft.width() / 2) + (BOXSIZE / 2);  //(tft.width() / 2) - (BOXSIZE / 2)
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
double verticalAlign = 35; //(tHeight - ((BOXSIZE * 4) + (padding * 3))) / 2
//Left column starting x posision
double leftColPositionX = center - fromCenter;
//Mid column starting x posision
double midColPositionX = center;
//Right column starting x posision
double rightColPositionX = center + fromCenter;

// Key values
#define row1MIN   64
#define row1MAX   105
#define row2MIN   121
#define row2MAX   169
#define row3MIN   184
#define row3MAX   232
#define row4MIN   248
#define row4MAX   290
#define col1MIN   102
#define col1MAX   177
#define col2MIN   204
#define col2MAX   272
#define col3MIN   296
#define col3MAX   365

///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

//EEPROM
#include <EEPROM.h>

//EEPROM
#define T0_EEPROM  0    //temp ambiente           -> EEPROM address
#define B_EEPROM   1    //constante calibración   -> EEPROM address
#define R_EEPROM   2    //resistencia LDR         -> EEPROM address

//General
uint16_t i;                 //read count
uint16_t j;                 //menu update

uint8_t menu;                   //menu number -> 0=Main, 1=LM35, 2=NTC, 3=PIR, 4=LDR, 99=keyboard
uint8_t menuBack;
String variableCalibration;

//Keyboard
String numberEntered;

//LM35 (Temperature)
#define pinLM35   A8
float LM35_volt, LM35_res, LM35_temp;

//NTC (Temperature)
#define pinNTC    A9
#define NTC_R1    10e3  // 10k ohms
#define NTC_R0    10e3
float NTC_volts, NTC_T, NTC_RT, NTC_AT = 0, NTC_R;
uint16_t NTC_T0;        //temperatura ambiente NTC
uint16_t NTC_B;         //constante de calibración NTC

//PIR (Motion)
#define pinPIR    30
int motionPIRstate;

//LDR (fotoresistance)
#define pinLDR    A10
#define pinLED    40
int fotoresistance;
String color;
#define colorWhiteMIN     830 //ok
#define colorWhiteMAX     840 //ok
#define colorBlackMIN     685 //ok
#define colorBlackMAX     795 //ok
#define colorBlueMIN      805 //ok
#define colorBlueMAX      805 //ok
#define colorRedMIN       764 //ok
#define colorRedMAX       774 //ok
#define colorYellowMIN    799 //ok
#define colorYellowMAX    820 //ok
/*#define A   1000     //Resistencia en oscuridad en KΩ
  #define B   15       //Resistencia a la luz (10 Lux) en KΩ
  #define Rc  10
  int ilum;*/
#define MAX_ADC_READING           1023
#define ADC_REF_VOLTAGE           5.0
#define REF_RESISTANCE_DEF        10000
#define LUX_CALC_SCALAR           12518931
#define LUX_CALC_EXPONENT         -1.405
int REF_RESISTANCE;

int   ldrRawData;
float resistorVoltage, ldrVoltage, ldrResistance, ldrLux;

void setup() {
  Serial.begin(9600);
  analogReference(DEFAULT);
  pinMode(3, OUTPUT);
  i = 0;
  j = 0;

  ///////////////////////
  ///     EEPROM      ///
  ///////////////////////
  //EEPROM.write(ADDRESS,VALUE);
  //EEPROM.update(T0_EEPROM, NTC_T0);
  //EEPROM.update(B_EEPROM, NTC_B);
  /*Serial.print("eeprom_NTC_T0,");
    Serial.println(NTC_T0);
    Serial.print("eeprom_NTC_B,");
    Serial.println(NTC_B);
    Serial.print("eeprom_LDR_R,");
    Serial.println(REF_RESISTANCE);*/

  //Read values from EEPROM
  NTC_T0 = EEPROM.read(T0_EEPROM);
  NTC_B = EEPROM.read(B_EEPROM);
  REF_RESISTANCE = EEPROM.read(R_EEPROM);
  REF_RESISTANCE = REF_RESISTANCE * 1000;

  ///////////////////////
  ///     SENSORS     ///
  ///////////////////////
  //PIR
  motionPIRstate = 0;         //initial state
  pinMode(pinPIR, INPUT);     //declare sensor as input

  //LDR
  fotoresistance = 0;
  pinMode(pinLED, OUTPUT);
  digitalWrite(pinLED, HIGH);

  ///////////////////////
  ///     TFT         ///
  ///////////////////////
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  tft.fillScreen(WHITE);              //Background color
  tft.setRotation(3);                 //(0, 1, 2, 3) -> (0, 90, 180, 270)

  ///////////////////////
  ///     MENU        ///
  ///////////////////////
  menu = 0;
  menuMain();
  pinMode(13, OUTPUT);

  defaultCalibration();
}

void loop() {
  ///////////////////////
  ///     MENU        ///
  ///////////////////////
  getPressed();

  ///////////////////////
  ///     SENSORS     ///
  ///////////////////////
  getSensors();
}

void defaultCalibration() {

}

void getPressed() {
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) { //if correct pressure
    // turn from 0->1023 to tft.width
    p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
    p.y = map(p.y, TS_MAXY, TS_MINY, 0, 480);

    /*Serial.print("p.y:"); // this code will help you get the y and x numbers for the touchscreen
      Serial.print(p.y);
      Serial.print(" ");
      Serial.print("p.x:");
      Serial.println(p.x);*/

    ///////////////////////
    ///     MAIN        ///
    ///////////////////////
    if (menu == 0) {
      //BUTTON LM35
      if (p.y >= 8 && p.y <= 238
          && p.x >= 94 && p.x <= 124) {
        //Serial.println("BUTTON LM35");
        menuLM35();
      }
      //BUTTON NTC
      if (p.y >= 8 && p.y <= 238
          && p.x >= 144 && p.x <= 174) {
        //Serial.println("BUTTON NTC");
        menuNTC();
      }
      //BUTTON PIR
      if (p.y >= 8 && p.y <= 238
          && p.x >= 194 && p.x <= 224) {
        //Serial.println("BUTTON PIR");
        menuPIR();
      }
      //BUTTON LDR
      if (p.y >= 8 && p.y <= 238
          && p.x >= 244 && p.x <= 274) {
        //Serial.println("BUTTON LDR");
        menuLDR();
      }
    }

    ///////////////////////
    ///     LM35        ///
    ///////////////////////
    if (menu == 1) {
      menuBack = 1;

      //RELOAD VALUES
      /*if (p.y >= 30 && p.y <= 420 && p.x >= 185 && p.x <= 235) {
        //Serial.println("BUTTON RELOAD");
        menuLM35();
        }*/

      //BUTTON MAIN MENU
      if (p.y >= 123 && p.y <= 352
          && p.x >= 264 && p.x <= 302) {
        //Serial.println("BUTTON MAIN");
        menuMain();
      }
    }

    ///////////////////////
    ///     NTC         ///
    ///////////////////////
    if (menu == 2) {
      menuBack = 2;

      //BUTTON CALIBRATE T0
      if (p.y >= 320 && p.y <= 380
          && p.x >= 50 && p.x <= 83) {
        //Serial.println("BUTTON CALIBRATE T0");
        variableCalibration = "NTC_T0";
        menuKeypad();
      }

      //BUTTON CALIBRATE B
      if (p.y >= 320 && p.y <= 380
          && p.x >= 100 && p.x <= 135) {
        //Serial.println("BUTTON CALIBRATE B");
        variableCalibration = "NTC_B";
        menuKeypad();
      }

      //BUTTON MAIN MENU
      if (p.y >= 123 && p.y <= 352
          && p.x >= 264 && p.x <= 302) {
        //Serial.println("BUTTON MAIN");
        menuMain();
      }
    }

    ///////////////////////
    ///     PIR         ///
    ///////////////////////
    if (menu == 3) {
      menuBack = 3;

      //BUTTON MAIN MENU
      if (p.y >= 123 && p.y <= 352
          && p.x >= 264 && p.x <= 302) {
        //Serial.println("BUTTON MAIN");
        menuMain();
      }
    }

    ///////////////////////
    ///     LDR         ///
    ///////////////////////
    if (menu == 4) {
      menuBack = 4;

      //BUTTON CALIBRATE R
      if (p.y >= 320 && p.y <= 380
          && p.x >= 50 && p.x <= 83) {
        //Serial.println("BUTTON CALIBRATE R");
        variableCalibration = "LDR_R";
        menuKeypad();
      }

      //BUTTON MAIN MENU
      if (p.y >= 123 && p.y <= 352
          && p.x >= 264 && p.x <= 302) {
        //Serial.println("BUTTON MAIN");
        menuMain();
      }
    }

    ///////////////////////
    ///     KEYPAD      ///
    ///////////////////////
    if (menu == 99) {

      delay(150);

      //ROW1
      if (p.x >= row1MIN && p.x <= row1MAX) {
        //COL1
        if (p.y >= col1MIN && p.y <= col1MAX) {
          Serial.println("key,1");
          numberEntered = numberEntered + "1";
          delay(150);
        }
        //COL2
        else if (p.y >= col2MIN && p.y <= col2MAX) {
          Serial.println("key,2");
          numberEntered = numberEntered + "2";
          delay(150);
        }
        //COL3
        else if (p.y >= col3MIN && p.y <= col3MAX) {
          Serial.println("key,3");
          numberEntered = numberEntered + "3";
          delay(150);
        }
      }

      //ROW2
      else if (p.x >= row2MIN && p.x <= row2MAX) {
        //COL1
        if (p.y >= col1MIN && p.y <= col1MAX) {
          Serial.println("key,4");
          numberEntered = numberEntered + "4";
          delay(150);
        }
        //COL2
        else if (p.y >= col2MIN && p.y <= col2MAX) {
          Serial.println("key,5");
          numberEntered = numberEntered + "5";
          delay(150);
        }
        //COL3
        else if (p.y >= col3MIN && p.y <= col3MAX) {
          Serial.println("key,6");
          numberEntered = numberEntered + "6";
          delay(150);
        }
      }

      //ROW3
      else if (p.x >= row3MIN && p.x <= row3MAX) {
        //COL1
        if (p.y >= col1MIN && p.y <= col1MAX) {
          Serial.println("key,7");
          numberEntered = numberEntered + "7";
          delay(150);
        }
        //COL2
        else if (p.y >= col2MIN && p.y <= col2MAX) {
          Serial.println("key,8");
          numberEntered = numberEntered + "8";
          delay(150);
        }
        //COL3
        else if (p.y >= col3MIN && p.y <= col3MAX) {
          Serial.println("key,9");
          numberEntered = numberEntered + "9";
          delay(150);
        }
      }

      //ROW4
      else if (p.x >= row4MIN && p.x <= row4MAX) {
        //COL1
        if (p.y >= col1MIN && p.y <= col1MAX) {
          Serial.println("key,0");
          numberEntered = numberEntered + "0";
          delay(150);
        }
        //COL2
        else if (p.y >= col2MIN && p.y <= col2MAX) {
          Serial.println("key,<-");
          if (numberEntered == "") {
            Serial.println("null");
          } else {
            numberEntered.remove(numberEntered.length() - 1, 1);
          }
          delay(150);
        }
        //COL3
        else if (p.y >= col3MIN && p.y <= col3MAX) {
          if (numberEntered == "") {
            Serial.println("null");
          } else {
            int updatedValue = numberEntered.toInt();
            /*Serial.print("numberEntered,");
              Serial.print(updatedValue);
              Serial.println("");*/

            //CALIBRATE NTC T0
            if (variableCalibration == "NTC_T0") {
              if (updatedValue <= 155) {
                EEPROM.update(T0_EEPROM, updatedValue);
                NTC_T0 = updatedValue;
                Serial.print("eeprom_NTC_T0,");
                Serial.println(updatedValue);
              } else {
                Serial.println("numberEntered,errorUPDATE_NTC_T0");
              }
            }

            //CALIBRATE NTC B
            else if (variableCalibration == "NTC_B") {
              if (updatedValue <= 50) {
                EEPROM.update(B_EEPROM, updatedValue);
                NTC_B = updatedValue;
                Serial.print("eeprom_NTC_B,");
                Serial.println(updatedValue);
              } else {
                Serial.println("numberEntered,errorUPDATE_NTC_B");
              }
            }

            //CALIBRATE LDR R
            else if (variableCalibration == "LDR_R") {
              if (updatedValue <= 15000) {
                EEPROM.update(R_EEPROM, updatedValue / 1000);
                REF_RESISTANCE = updatedValue;
                Serial.print("eeprom_LDR_R,");
                Serial.println(updatedValue);
              } else {
                Serial.println("numberEntered,errorUPDATE_LDR_R");
              }
            }

            numberEntered = "";
          }
          delay(150);

          switch (menuBack) {
            case 2:
              menuNTC();
              break;
            case 4:
              menuLDR();
              break;
          }
        }

      }

    }
  }
}

