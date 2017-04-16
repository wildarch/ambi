/*
  GraphicsLib Demo

  This sketch demonstrates the functions of the GraphicsLib.
 */

#include <Wire.h>
#include <SPI.h>
#include <digitalWriteFast.h>
#include <GraphicsLib.h>
#include <SSD1331.h>
#include <S65L2F50.h>
#include <S65LPH88.h>
#include <S65LS020.h>
#include <MI0283QT2.h>
#include <MI0283QT9.h>
#include <DisplaySPI.h>
#include <DisplayI2C.h>
#include <BMPheader.h>


//Declare only one display !
// SSD1331 lcd;
// S65L2F50 lcd;
// S65LPH88 lcd;
// S65LS020 lcd;
// MI0283QT2 lcd;  //MI0283QT2 Adapter v1
MI0283QT9 lcd;  //MI0283QT9 Adapter v1
// DisplaySPI lcd; //SPI (GLCD-Shield or MI0283QT Adapter v2)
// DisplayI2C lcd; //I2C (GLCD-Shield or MI0283QT Adapter v2)


void setup()
{
  uint8_t clear_bg=0x00; //0x80 = dont clear background for fonts (only for DisplayXXX)

  //init display
  lcd.begin();
  Serial.begin(115200);
  //SPI Displays
//  lcd.begin(); //spi-clk=Fcpu/4
//  lcd.begin(SPI_CLOCK_DIV2); //spi-clk=Fcpu/2
//  lcd.begin(SPI_CLOCK_DIV4, 8); //spi-clk=Fcpu/4, rst-pin=8
  //I2C Displays
  // lcd.begin(0x20); //addr=0x20
  // lcd.begin(0x20, 8); //addr=0x20, rst-pin=8


  //clear screen
  lcd.fillScreen(RGB(0,0,0));
}

void drawHappyMouth() {
  lcd.fillCircle(160, 115, 115, RGB(255, 255, 255));
  lcd.fillCircle(160, 80, 130, RGB(0, 0, 0));
}

#define EYE_LX 78
#define EYE_RX 233
#define EYE_Y 73
#define EYE_BG_R 38

void drawEyesBG() {
  lcd.fillCircle(EYE_LX, EYE_Y, EYE_BG_R, RGB(255,255,255));
  lcd.fillCircle(EYE_RX, EYE_Y, EYE_BG_R, RGB(255,255,255));
}

void drawHappy() {
  drawHappyMouth();
}

// 0 <= 1
void drawEyesPhase(float t) {
  float phase = 2 * PI * t;
  int xOff = cos(phase) * (EYE_BG_R / 2);
  int yOff = sin(phase) * (EYE_BG_R / 2);
  lcd.fillCircle(EYE_LX + xOff, EYE_Y + yOff, 13, RGB(0, 0, 255));
  lcd.fillCircle(EYE_RX + xOff, EYE_Y + yOff, 13, RGB(0, 0, 255));
}

void loop()
{
  for (float t = 0; t < 1; t += 0.1) {
    drawEyesBG();
    drawEyesPhase(t);
  }
  /*
  Serial.println("Let's draw some images!");
  
  uint16_t left = RGB(255,0,0);
  uint16_t right = RGB(0,255,0);
  for(uint16_t x = 0; x < 320; x++) {
    for(uint16_t y = 0; y < 240; y++) {
      uint16_t pixel = 0;
      while (!Serial.available()) {};
      pixel |= Serial.read() << 8;
      while (!Serial.available()) {};
      pixel |= Serial.read();
      lcd.drawPixel(x, y, pixel);
      
    }
  }

  delay(10000);
  lcd.fillScreen(RGB(0, 0, 0));
  */
}


/*
uint8_t OpenBMPFile(int16_t x, int16_t y)
{
  uint8_t buf[40]; //read buf (min. size = sizeof(BMP_DIPHeader))
  BMP_Header *bmp_hd;
  BMP_DIPHeader *bmp_dip;
  int16_t width, height, w, h;
  uint8_t pad, result=0;
  
    //myFile.read(&buf, sizeof(BMP_Header));
    readBytes(buf, (int) sizeof(BMP_Header));
    bmp_hd = (BMP_Header*)&buf[0];
    if((bmp_hd->magic[0] == 'B') && (bmp_hd->magic[1] == 'M') && (bmp_hd->offset == 54))
    {
      result = 2;
      //BMP DIP-Header
      //myFile.read(&buf, sizeof(BMP_DIPHeader));
      readBytes(buf, (int) sizeof(BMP_DIPHeader));
      bmp_dip = (BMP_DIPHeader*)&buf[0];
      if((bmp_dip->size == sizeof(BMP_DIPHeader)) && (bmp_dip->bitspp == 24) && (bmp_dip->compress == 0))
      {
        result = 3;
        //BMP Data (1. pixel = bottom left)
        width  = bmp_dip->width;
        height = bmp_dip->height;
        pad    = width % 4; //padding (line is multiply of 4)
        if((x+width) <= lcd.getWidth() && (y+height) <= lcd.getHeight())
        {
          result = 4;
          lcd.setArea(x, y, x+width-1, y+height-1);
          for(h=(y+height-1); h >= y; h--) //for every line
          {
            for(w=x; w < (x+width); w++) //for every pixel in line
            {
              //myFile.read(&buf, 3);
              readBytes(buf, (int) 3);
              lcd.drawPixel(w, h, RGB(buf[2],buf[1],buf[0]));
            }
            if(pad)
            {
              //myFile.read(&buf, pad);
              readBytes(buf, pad);
            }
          }
        }
        else
        {
          lcd.drawText(x, y, "Pic out of screen!", RGB(0,0,0), RGB(255,255,255), 1);
        }
      }
      else {
        lcd.drawText(x, y, "Nope1", RGB(0,0,0), RGB(255,255,255), 1);
        return 0;
      }
    }
    else {
      lcd.drawText(x, y, "Nope2", RGB(0,0,0), RGB(255,255,255), 1);
      return 0;
    }
  
  return result;
}
*/
