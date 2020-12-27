#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SH1106 display(OLED_RESET);


static const unsigned char PROGMEM logo_bmp[] =
{ B01000111, B11100010,
  B01100100, B00100110,
  B01110100, B00101110,
  B01111100, B00111110,
  B01100000, B00000110,
  B00110000, B00001100,
  B00011000, B00011000,
  B00001100, B00110000,
  B00000100, B00100000,
  B00000100, B00100000,
  B00000100, B00100000,
  B00011100, B00111000,
  B00001100, B00110000,
  B00000110, B01100000,
  B00000011, B11000000,
  B00000001, B10000000 };

#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

int rectX = (display.width()/2)-14;
int rectY = display.height()-6;
int bitX = (display.width()/2)-8;
int bitY = 0;
int score = 0;
int speed = 1;
int rectW = 28;
int digPause = 0;
int digLeft = 0;
int digRight = 0;
//int pace = 50;

void setup() {
//Serial.begin(115200);
Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  display.clearDisplay();
}

void loop() {

  digLeft = digitalRead(2);
  digRight = digitalRead(3);
  digPause = digitalRead(4);

  //player controls
  if((digLeft == LOW) && (rectX >= 0)){
    rectX = (rectX - (speed * 3));
  }
  else if((digRight == LOW) && (rectX <= (display.width() - rectW))){
    rectX = (rectX + (speed * 3));
  }
  else if(digPause == LOW){
    pause();
  }
  else{
    
  }
  //torpedo logics
  bitY = bitY + speed;
  if(bitY >= (rectY-15)){
    if((bitX + 8)<=rectX || (bitX + 7)>=(rectX + rectW)){
      lose();
    }
    else{
        proceed();
      }
    bitY = 0;
    bitX = random(1, (display.width()-16));
  }
  display.clearDisplay();
  
  //info overlay - you may comment out this
  info();

  display.drawBitmap(bitX, bitY, logo_bmp, 16, 16, 1);
  display.fillRect(rectX, rectY, rectW, 6, WHITE);
  display.display();

  //for slower first level
  //delay(pace);
}




void explosion(void) {
  display.clearDisplay();
  for(int16_t i=0; i<max(display.width(),display.height()); i+=2) {
    display.drawCircle((bitX + 7), display.height(), i, WHITE);
    display.display();
    delay(1);
  }
}


void pause(void){
  delay(300);
  while (true) {
    digPause = digitalRead(4);  
    display.clearDisplay();
    display.setTextSize(2);      
    display.setTextColor(WHITE); 
    display.setCursor(30, 20);
    display.println("PAUSE");
    display.setTextSize(1);
    display.setCursor(10, 40);
    display.print("CURRENT SCORE: ");
    display.println(score);
    display.display();
    delay(50);
    if (digPause == LOW){break;} 
    }
}


void lose(void){
  explosion();
  delay(1000);
  display.clearDisplay();
  display.setTextSize(2);      
  display.setTextColor(WHITE); 
  display.setCursor(5, 20);
  display.print("SCORE: ");
  display.println(score);
  display.display();
  delay(2500);
  score = 0;
  rectW = 28;
  speed = 1;
  
  //for slower first level
  //pace = 50;
}


void proceed(void){
  score = (score + 1);

  //for variable (slower) pace of first level
  //if(((score % 2) == 0) && (pace > 1)){pace = (pace - 5);}
  
  if(((score % 15) == 0) && (score > 0)){rectW = 18;}
  
  if(((score % 30) == 0) && (score > 0)){
    speed = (speed + 1);
    rectW = 28;
    }
}

void info(void){
  display.setTextSize(1);      
  display.setTextColor(WHITE); 
  display.setCursor(1, 0);
  display.println(score);
  display.setCursor((display.width()-8), 0); //set the distance bigger if you use variable pace
  display.print(speed);
  //display.print("-");
  //display.print((55 - pace) / 5);
}
