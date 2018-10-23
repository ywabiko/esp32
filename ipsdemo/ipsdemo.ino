// IPS LCD sample for ESP32 for 1.3" 240x240 and 0.96" 160x80
//
//   - 1.3"  240x240
//       LCD     ESP32
//       GND --- GND
//       VCC --- 3V3
//       SCL --- GPIO#18 (VSPI SCK)
//       SDA --- GPIO#23 (VSPI MOSI)
//       RES --- GPIO#33
//       DC  --- GPIO#32
//       BLK --- (unused)
//
//   - 0.96" 160x80
//       LCD     ESP32
//       GND --- GND
//       VCC --- 3V3
//       SCL --- GPIO#18 (VSPI SCK)
//       SDA --- GPIO#23 (VSPI MOSI)
//       RES --- GPIO#33
//       DC  --- GPIO#32
//       CS  --- GPIO#5 (VSPI CS)
//       BLK --- (unused)
//
// To test 1.3", define USE_IPS_240x240.
// To test 0.96", undefine USE_IPS_240x240.
//
// This work is derived from graphicstest in Adafruit-GRFX-Library.
// https://github.com/adafruit/Adafruit-GFX-Library
// 
// This work is licensed under the Creative Commons Attribution 4.0
// International License. To view a copy of this license, visit
// http://creativecommons.org/licenses/by/4.0/ or send a letter to
// Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.



// LCD panel selection
// For 1.3" 240x240, define this.
// For 0.96" 160x80, undefine this.
//#define USE_IPS_240x240


#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

// 1.3" 240x240 Software SPI
#ifdef USE_IPS_240x240
#define TFT_CS     -1  // BLK pin has to be open. To do so, specifying any unused pin here is the easiest way.
#define TFT_RST    33
#define TFT_DC     32
#define TFT_SCLK   18
#define TFT_MOSI   23
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
#endif

// 0.96" 180x60 Hardware SPI
#ifndef USE_IPS_240x240
#define TFT_CS     5
#define TFT_RST    33
#define TFT_DC     32
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
#endif

float p = 3.1415926;

SPIClass vspi;

void setup(void) {
     Serial.begin(115200);
     Serial.print("Hello! ST77xx TFT Test");
     pinMode(TFT_RST, OUTPUT);
     pinMode(TFT_DC, OUTPUT);
     pinMode(TFT_CS, OUTPUT);

#ifdef USE_IPS_240x240
     // 1.3" 240x240 TFT
     tft.init(240, 240);   // initialize a ST7789 chip, 240x240 pixels
#else
     // 0.96" 160x80
     tft.initR(INITR_MINI160x80);   // initialize a ST7735S chip, mini display
#endif


     Serial.println("Initialized");

     uint16_t time = millis();
     tft.fillScreen(ST77XX_BLACK);
     time = millis() - time;

     Serial.println(time, DEC);
     delay(500);

     // large block of text
     tft.fillScreen(ST77XX_BLACK);
     testdrawtext("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur adipiscing ante sed nibh tincidunt feugiat. Maecenas enim massa, fringilla sed malesuada et, malesuada sit amet turpis. Sed porttitor neque ut ante pretium vitae malesuada nunc bibendum. Nullam aliquet ultrices massa eu hendrerit. Ut sed nisi lorem. In vestibulum purus a tortor imperdiet posuere. ", ST77XX_WHITE);
     delay(1000);

     // tft print function!
     tftPrintTest();
     delay(4000);

     // a single pixel
     tft.drawPixel(tft.width()/2, tft.height()/2, ST77XX_GREEN);
     delay(500);

     // line draw test
     testlines(ST77XX_YELLOW);
     delay(500);

     // optimized lines
     testfastlines(ST77XX_RED, ST77XX_BLUE);
     delay(500);

     testdrawrects(ST77XX_GREEN);
     delay(500);

     testfillrects(ST77XX_YELLOW, ST77XX_MAGENTA);
     delay(500);

     tft.fillScreen(ST77XX_BLACK);
     testfillcircles(10, ST77XX_BLUE);
     testdrawcircles(10, ST77XX_WHITE);
     delay(500);

     testroundrects();
     delay(500);

     testtriangles();
     delay(500);

     mediabuttons();
     delay(500);

     Serial.println("done");
     delay(1000);
}

void loop() {
     tft.invertDisplay(true);
     delay(500);
     tft.invertDisplay(false);
     delay(500);
}

void testlines(uint16_t color) {
     tft.fillScreen(ST77XX_BLACK);
     for (int16_t x=0; x < tft.width(); x+=6) {
          tft.drawLine(0, 0, x, tft.height()-1, color);
     }
     for (int16_t y=0; y < tft.height(); y+=6) {
          tft.drawLine(0, 0, tft.width()-1, y, color);
     }

     tft.fillScreen(ST77XX_BLACK);
     for (int16_t x=0; x < tft.width(); x+=6) {
          tft.drawLine(tft.width()-1, 0, x, tft.height()-1, color);
     }
     for (int16_t y=0; y < tft.height(); y+=6) {
          tft.drawLine(tft.width()-1, 0, 0, y, color);
     }

     tft.fillScreen(ST77XX_BLACK);
     for (int16_t x=0; x < tft.width(); x+=6) {
          tft.drawLine(0, tft.height()-1, x, 0, color);
     }
     for (int16_t y=0; y < tft.height(); y+=6) {
          tft.drawLine(0, tft.height()-1, tft.width()-1, y, color);
     }

     tft.fillScreen(ST77XX_BLACK);
     for (int16_t x=0; x < tft.width(); x+=6) {
          tft.drawLine(tft.width()-1, tft.height()-1, x, 0, color);
     }
     for (int16_t y=0; y < tft.height(); y+=6) {
          tft.drawLine(tft.width()-1, tft.height()-1, 0, y, color);
     }
}

void testdrawtext(char *text, uint16_t color) {
     tft.setCursor(0, 0);
     tft.setTextColor(color);
     tft.setTextWrap(true);
     tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2) {
     tft.fillScreen(ST77XX_BLACK);
     for (int16_t y=0; y < tft.height(); y+=5) {
          tft.drawFastHLine(0, y, tft.width(), color1);
     }
     for (int16_t x=0; x < tft.width(); x+=5) {
          tft.drawFastVLine(x, 0, tft.height(), color2);
     }
}

void testdrawrects(uint16_t color) {
     tft.fillScreen(ST77XX_BLACK);
     for (int16_t x=0; x < tft.width(); x+=6) {
          tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
     }
}

void testfillrects(uint16_t color1, uint16_t color2) {
     tft.fillScreen(ST77XX_BLACK);
     for (int16_t x=tft.width()-1; x > 6; x-=6) {
          tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
          tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
     }
}

void testfillcircles(uint8_t radius, uint16_t color) {
     for (int16_t x=radius; x < tft.width(); x+=radius*2) {
          for (int16_t y=radius; y < tft.height(); y+=radius*2) {
               tft.fillCircle(x, y, radius, color);
          }
     }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
     for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
          for (int16_t y=0; y < tft.height()+radius; y+=radius*2) {
               tft.drawCircle(x, y, radius, color);
          }
     }
}

void testtriangles() {
     tft.fillScreen(ST77XX_BLACK);
     int color = 0xF800;
     int t;
     int w = tft.width()/2;
     int x = tft.height()-1;
     int y = 0;
     int z = tft.width();
     for(t = 0 ; t <= 15; t++) {
          tft.drawTriangle(w, y, y, x, z, x, color);
          x-=4;
          y+=4;
          z-=4;
          color+=100;
     }
}

void testroundrects() {
     tft.fillScreen(ST77XX_BLACK);
     int color = 100;
     int i;
     int t;
     for(t = 0 ; t <= 4; t+=1) {
          int x = 0;
          int y = 0;
          int w = tft.width()-2;
          int h = tft.height()-2;
          for(i = 0 ; i <= 16; i+=1) {
               tft.drawRoundRect(x, y, w, h, 5, color);
               x+=2;
               y+=3;
               w-=4;
               h-=6;
               color+=1100;
          }
          color+=100;
     }
}

void tftPrintTest() {
     tft.setTextWrap(false);
     tft.fillScreen(ST77XX_BLACK);
     tft.setCursor(0, 30);
     tft.setTextColor(ST77XX_RED);
     tft.setTextSize(1);
     tft.println("Hello World!");
     tft.setTextColor(ST77XX_YELLOW);
     tft.setTextSize(2);
     tft.println("Hello World!");
     tft.setTextColor(ST77XX_GREEN);
     tft.setTextSize(3);
     tft.println("Hello World!");
     tft.setTextColor(ST77XX_BLUE);
     tft.setTextSize(4);
     tft.print(1234.567);
     delay(1500);
     tft.setCursor(0, 0);
     tft.fillScreen(ST77XX_BLACK);
     tft.setTextColor(ST77XX_WHITE);
     tft.setTextSize(0);
     tft.println("Hello World!");
     tft.setTextSize(1);
     tft.setTextColor(ST77XX_GREEN);
     tft.print(p, 6);
     tft.println(" Want pi?");
     tft.println(" ");
     tft.print(8675309, HEX); // print 8,675,309 out in HEX!
     tft.println(" Print HEX!");
     tft.println(" ");
     tft.setTextColor(ST77XX_WHITE);
     tft.println("Sketch has been");
     tft.println("running for: ");
     tft.setTextColor(ST77XX_MAGENTA);
     tft.print(millis() / 1000);
     tft.setTextColor(ST77XX_WHITE);
     tft.print(" seconds.");
}

void mediabuttons() {
     // play
     tft.fillScreen(ST77XX_BLACK);
     tft.fillRoundRect(25, 10, 78, 60, 8, ST77XX_WHITE);
     tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_RED);
     delay(500);
     // pause
     tft.fillRoundRect(25, 90, 78, 60, 8, ST77XX_WHITE);
     tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_GREEN);
     tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_GREEN);
     delay(500);
     // play color
     tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_BLUE);
     delay(50);
     // pause color
     tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_RED);
     tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_RED);
     // play color
     tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_GREEN);
}

