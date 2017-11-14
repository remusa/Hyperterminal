void menuKeypad() {
  menu = 99;
  
  createKeyboard();
}

void createKeyboard() {
  //TITLE
  tft.fillScreen(WHITE);
  tft.setCursor(120, 10);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.print("TECLADO");

  //(initial x,initial y,width,height,color)
  double secondRowVertialAlign = secondRow + verticalAlign;
  double thirdRowVertialAlign = thirdRow + verticalAlign;
  double fourthRowVertialAlign = fourthRow + verticalAlign;

  ///////////////////////
  ///  DRAW KEYBOARD  ///
  ///////////////////////
  //First Row
  tft.fillRect(leftColPositionX, verticalAlign, BOXSIZE, BOXSIZE, RED);
  tft.fillRect(midColPositionX, verticalAlign, BOXSIZE, BOXSIZE, RED);
  tft.fillRect(rightColPositionX, verticalAlign, BOXSIZE, BOXSIZE, RED);
  //Second Row
  tft.fillRect(leftColPositionX, secondRowVertialAlign, BOXSIZE, BOXSIZE, RED);
  tft.fillRect(midColPositionX, secondRowVertialAlign, BOXSIZE, BOXSIZE, RED);
  tft.fillRect(rightColPositionX, secondRowVertialAlign, BOXSIZE, BOXSIZE, RED);
  //Third Row
  tft.fillRect(leftColPositionX, thirdRowVertialAlign, BOXSIZE, BOXSIZE, RED);
  tft.fillRect(midColPositionX, thirdRowVertialAlign, BOXSIZE, BOXSIZE, RED);
  tft.fillRect(rightColPositionX, thirdRowVertialAlign, BOXSIZE, BOXSIZE, RED);
  //Fourth Row
  tft.fillRect(leftColPositionX, fourthRowVertialAlign, BOXSIZE, BOXSIZE, RED);
  tft.fillRect(midColPositionX, fourthRowVertialAlign, BOXSIZE, BOXSIZE, RED);
  tft.fillRect(rightColPositionX, fourthRowVertialAlign, BOXSIZE, BOXSIZE, RED);

  ///////////////////////
  ///  DRAW BORDERS   ///
  ///////////////////////
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
  tft.drawRect(leftColPositionX, fourthRowVertialAlign, BOXSIZE, BOXSIZE, BLACK);
  tft.drawRect(midColPositionX, fourthRowVertialAlign, BOXSIZE, BOXSIZE, BLACK);
  tft.drawRect(rightColPositionX, fourthRowVertialAlign, BOXSIZE, BOXSIZE, BLACK);

  ///////////////////////
  /// INSERT NUMBERS  ///
  ///////////////////////
  //Centers text horizontally on all three columns
  double leftColCursorX   = leftColPositionX + (BOXSIZE / 3);
  double midColCursorX    = midColPositionX  + (BOXSIZE / 3);
  double rightColCursorX  = rightColPositionX + (BOXSIZE / 3);
  //Centers text horizontally on all four rows
  double firstRowCursorY  = verticalAlign + (BOXSIZE / 3);
  double secondRowCursorY = secondRow + firstRowCursorY;
  double thirdRowCursorY  = thirdRow  + firstRowCursorY;
  double fourthRowCursorY = fourthRow + firstRowCursorY;

  tft.setTextSize(2);
  tft.setTextColor(WHITE);

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
  tft.setCursor(leftColCursorX, fourthRowCursorY);
  tft.println("0");
  //Insert Back Character
  tft.setCursor(midColCursorX, fourthRowCursorY);
  tft.println("<-");
  //Insert Enter Character
  tft.setCursor(rightColCursorX, fourthRowCursorY);
  tft.println("->");
}

