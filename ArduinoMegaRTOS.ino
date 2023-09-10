#include <Arduino_FreeRTOS.h>
#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h"
#include "Math.h"
#include <TouchScreen.h>



MCUFRIEND_kbv tft;
char *name = "Sound System";  //edit name of shield
const int XP=8,XM=A2,YP=A3,YM=9; //240x320 ID=0x7789
const int TS_LEFT=120,TS_RT=905,TS_TOP=90,TS_BOT=895;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

#define MINPRESSURE 200
#define MAXPRESSURE 1000

int16_t BOXSIZE;
int16_t PENRADIUS = 1;
uint16_t ID, oldcolor, currentcolor;
uint8_t Orientation = 0;    //PORTRAIT




#define YP A2 
#define XM A1 
#define YM 6  
#define XP 7 
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GREY    0x8410
#define ORANGE  0xE880
int x = 0;
const int ledPin = 52;

const int ldrPin = A8;


int VRx = A9;
int VRy = A10;
int SW = 53;
const int g = 32;
const int f = 34; 
const int a = 36; 
const int b = 38;
const int e = 33;
const int d = 35; 
const int c = 37;
const int dp = 49;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
//---------------------------------------------------
SoftwareSerial softwareSerial(30, 31);
DFRobotDFPlayerMini player;
char comm[5];
int begin = 0;

void displaySong(){
  Serial.print(x);
  //tft.fillRect(0,270,100,100,BLACK);
  if(x==0){
  tft.setCursor(13,270);
  tft.println("Weird Fishes");
  }
  if (x==5){
    tft.setCursor(12,270);
    tft.println("Pyramid Song");
  }
  if (x==2){
    tft.setCursor(30,270);
    tft.println("All I Need");
  }
  if (x==1){
    tft.setCursor(4,270);
    tft.println("Bodysnatchers");
  
  }
   if (x==4){
    tft.setCursor(21,270);
    tft.println("Daydreaming");
  }
   if (x==3){
    tft.setCursor(30,270);
    tft.println("Man Of War");
  }
}

void playNext(){
  if(x<=4){
  x++;
  }else{
    x = 0;
  }
  
}
void playPrev(){
  if(x!=0){
  x--;
  }
}

void redisplay(){
  tft.reset();
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.invertDisplay(false);
  tft.fillScreen(BLACK);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.fillRect(0,0,120,120,GREEN);
  tft.fillRect(120,0,120,120,RED);
  tft.setCursor(16,45);
  tft.println("Pause");
  tft.setCursor(145,45);
  tft.println("Play");
   tft.fillRect(120,120,120,120,GREY);
  tft.fillRect(0,120,120,120,BLUE);
  tft.setCursor(16,165);
  tft.println("Prev.");
  tft.setCursor(145,165);
  tft.println("Next");
  displaySong();
}


void mp3_player(void *pvparameters){
  TickType_t xLastWakeTime;
  const TickType_t xDelay1s = pdMS_TO_TICKS(500);
  tft.reset();
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.invertDisplay(false);
  tft.fillScreen(BLACK);
  tft.setTextSize(2);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.fillRect(0,0,120,120,GREEN);
  tft.fillRect(120,0,120,120,RED);
  tft.setCursor(16,45);
  tft.println("Pause");
  tft.setCursor(145,45);
  tft.println("Play");
   tft.fillRect(120,120,120,120,GREY);
  tft.fillRect(0,120,120,120,BLUE);
  tft.setCursor(16,165);
  tft.println("Prev.");
  tft.setCursor(145,165);
  tft.println("Next");
  displaySong();
  softwareSerial.begin(9600);
  player.begin(softwareSerial);

  while(1){
    //displaySong();
  if(begin==0){player.start();begin=1;}
    uint16_t xp, y;  
    tp = ts.getPoint();   
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE) {
        xp = map(tp.x, TS_LEFT, TS_RT, 0, tft.width());
        y = map(tp.y, TS_TOP, TS_BOT, 0, tft.height());
      if(xp>120 && xp <240){
          if(y>120 && y <240){
            playNext();
            delay(100);
            player.next();
            
           // setup();
            Serial.write("Next\n");
            Serial.print(x);
            tft.fillRect(0,270,100,100,GREEN);
            //delay(1000);
            //serial.write
            redisplay();
            

          }
      }
      if(xp>1 && xp <120){
          if(y>120 && y <240){
            playPrev();
            delay(100);
           // setup();
            Serial.write("Prev\n");
            //Serial.write(x);
            player.previous();
            redisplay();

          }
      }
      if(xp>1 && xp <120){
          if(y>0 && y <120){
            Serial.write("Pause\n");
            player.pause();

          }
      }
      if(xp>120 && xp <240){
          if(y>0 && y <120){
            Serial.write("Play\n");
            player.start();            

          }
      }
    }
    //displaySong();
    vTaskDelayUntil(xLastWakeTime,xDelay1s);
    
  }
}

void lights(void *pvparameters){
  //Serial.begin(9600);

  pinMode(ledPin, OUTPUT);

  pinMode(ldrPin, INPUT);
  TickType_t xLastWakeTime;
  const TickType_t xDelay1s = pdMS_TO_TICKS(5000);
  while(1){
    int ldrStatus = analogRead(ldrPin);

     if (ldrStatus <= 200) {

        digitalWrite(ledPin, LOW);

        Serial.print("Its DARK, Turn on the LED : ");

       Serial.println(ldrStatus);
       vTaskDelayUntil(xLastWakeTime,xDelay1s);

     } else {

        digitalWrite(ledPin, HIGH);

        Serial.print("Its BRIGHT, Turn off the LED : ");

        Serial.println(ldrStatus);

  }
  //delay(1000);
  }

}


void N(){
   digitalWrite (g, LOW);digitalWrite (f, HIGH);digitalWrite (a, HIGH);digitalWrite (b, HIGH);digitalWrite (e, LOW);digitalWrite (d, HIGH);digitalWrite (c, LOW);digitalWrite (dp, LOW);
}

void D(){
  digitalWrite (g, LOW);digitalWrite (f, HIGH);digitalWrite (a, HIGH);digitalWrite (b, LOW);digitalWrite (e, LOW);digitalWrite (d, LOW);digitalWrite (c, LOW);digitalWrite (dp, LOW);
}

void R(){
   digitalWrite (g, LOW);digitalWrite (f, HIGH);digitalWrite (a, HIGH);digitalWrite (b, HIGH);digitalWrite (e, LOW);digitalWrite (d, HIGH);digitalWrite (c, HIGH);digitalWrite (dp, LOW);

 }

 void P(){
  digitalWrite (g, LOW);digitalWrite (f, LOW);digitalWrite (a, LOW);digitalWrite (b, LOW);digitalWrite (e, LOW);digitalWrite (d, HIGH);digitalWrite (c, HIGH);digitalWrite (dp, LOW);
 }
  
void joysegment(){
  pinMode(g,OUTPUT);pinMode(f,OUTPUT);pinMode(a,OUTPUT);pinMode(b,OUTPUT);
  pinMode(e,OUTPUT);pinMode(d,OUTPUT);pinMode(c,OUTPUT);pinMode(dp,OUTPUT);
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP); 

  while(1){
    xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  
  //Serial.print("X: ");
 // Serial.print(mapX);
  //Serial.print(" | Y: ");
 // Serial.print(mapY);
 // Serial.print(" | Button: ");
 // Serial.println(SW_state);

  if(mapX>500){
  Serial.println("UP");
    D();


  }

  if(mapX<-510){
  Serial.println("DOWN");
   R();

  }
  if(mapY>500){
  Serial.println("RIGHT");
    N();

  }

  if(mapY<-510){
  Serial.println("LEFT");
   P();

  }

  delay(100);
  }
}
void setup() {
  xTaskCreate(lights,"LED",256,NULL,2,NULL);
  xTaskCreate(mp3_player,"MP3",5120,NULL,2,NULL);
  xTaskCreate(joysegment,"joystick",256,NULL,2,NULL);
}

void loop() {
  // put your main code here, to run repeatedly:

}
