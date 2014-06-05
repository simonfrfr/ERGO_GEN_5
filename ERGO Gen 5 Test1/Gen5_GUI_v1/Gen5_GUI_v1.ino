#include <ITDB02_Graph16.h>

//Declare which fonts we will be using
extern uint8_t ERGO_Font[];
String unitid = "1337";
int k = 0;
//Shield
ITDB02 myGLCD(19,18,17,16);
void setup()
{
  randomSeed(analogRead(0));
  
  // Setup the LCD
  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.setFont(ERGO_Font);
  
}

void loop()
{
  int buf[318];
  int x, x2;
  int y, y2;
  int r;
  
// Clear the screen and draw the frame
//  myGLCD.clrScr();
if (k == 0) {
  myGLCD.clrScr();
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRect(80, 240, 240, 215);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(255, 0, 0);
  String words = "*** ERGO - "+ unitid + " ***";
  myGLCD.print(&words[0], CENTER, 220);
  myGLCD.setColor(255,255,255);
  myGLCD.drawLine(79, 0, 79, 240);
  myGLCD.setColor(255,255,255);
  myGLCD.drawLine(240,0,240,240);
  myGLCD.setColor(255,255,255);
  myGLCD.drawLine(0, 50, 79, 50);
  myGLCD.setColor(255, 255, 255);
  myGLCD.setBackColor(0, 0, 0);
  myGLCD.print("ERGO", CENTER, 1);
  myGLCD.setColor(0,0,255);
  myGLCD.fillRoundRect(5,5,74,45);
  myGLCD.setColor(255,255,255);
  myGLCD.setBackColor(0,0,255);
  myGLCD.print("<- All", 5, 10);
  myGLCD.print("  Units", 5, 25);
  k = 1;
}
  
  //delay(10000);
}

