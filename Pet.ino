#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
const int bathroom = 4; 
const int feed = 3;
const int stats = 2;
const int play = 5;
const int buzzer = 9;

int hunger = 0;
int happiness = 24;
int restroom = 0;
int value = 0; 

int Display = 1;
int ON = 1;

unsigned long currentMillis, previousMillis;
const unsigned long interval = 3600000;// 3600000

unsigned long currentMillis2, previousMillis2;
const unsigned long interval2 = 30000;// 3600000

Adafruit_SSD1306 display(OLED_RESET);

static const unsigned char PROGMEM dino[] ={
B00000000, B00000000,
B00000000, B00000000,  
B00000000, B00000000, 
B00000111, B11110000,  
B01111001, B00111000, 
B10000000, B00011100, 
B11111111, B00001100, 
B00000001, B00001100, 
B00111110, B00001100, 
B00010000, B10100100, 
B00010000, B01000100, 
B00010000, B00000100,  
B00010000, B00001000, 
B00001011, B01110000, 
B00001011, B01000000, 
B00000100, B10000000,
};

static const unsigned char PROGMEM tree[] ={
B00000000, B00000000, 
B00011110, B01111000, 
B01100001, B10000110,  
B10001111, B11110001, 
B01010001, B10001010, 
B00100001, B10000100, 
B00000011, B10010000, 
B00101101, B10110000, 
B00010001, B11001000, 
B00000001, B10000000, 
B00000001, B10000000,  
B00000011, B11000000, 
B00000111, B11100000, 
B00000111, B11100000, 
B00011111, B11111000,
};

static const unsigned char PROGMEM sun[] ={
B00000111, B11111110,
B00011000, B00000001,
B00101011, B00001101,
B00011011, B00001101,
B00101000, B01100001,
B00011000, B00000001,
B00000111, B11111110,
B00000010, B10101010,
B00000000, B01000100,
B00000000, B00000000,
B00000000, B00000000,
B00000000, B00000000,
B00000000, B00000000,
B00000000, B00000000,
B00000000, B00000000,
B00000000, B00000000
};

static const unsigned char PROGMEM cloud[] ={
B00011111, B11111000, 
B01110000, B00001110, 
B11000110, B01100011,  
B10000110, B01100001, 
B11000000, B00000011, 
B01110000, B00001110, 
B00011111, B11111000, 
B00000000, B00000000, 
B00000000, B00000000, 
B00000000, B00000000, 
B00000000, B00000000,  
B00000000, B00000000, 
B00000000, B00000000, 
B00000000, B00000000, 
B00000000, B00000000,
B00000000, B00000000,
};

static const unsigned char PROGMEM chair[] ={
B00000000, B00000000, 
B00000000, B00000000, 
B00000000, B00000000,  
B00000000, B00000000, 
B00000000, B00000000, 
B00010000, B00000000, 
B00010000, B00000000, 
B00010000, B00000000, 
B00010000, B00000000, 
B00010000, B00000000, 
B00011111, B11111000,  
B00010000, B00001000, 
B00010000, B00001000, 
B00010000, B00001000, 
B00010000, B00001000,
};

static const unsigned char PROGMEM lamp[] ={
B00000000, B00000000, 
B00000011, B11000000, 
B00000111, B11100000,  
B00001111, B11110000, 
B00001111, B11110000, 
B00000001, B10100000, 
B00000001, B10100000, 
B00000001, B10000000, 
B00000001, B10000000, 
B00000001, B10000000, 
B00000001, B10000000,  
B00000001, B10000000, 
B00000001, B10000000, 
B00000001, B10000000, 
B00001111, B11110000,
};

static const unsigned char PROGMEM ptg[] ={
B11111111, B11110000, 
B10000000, B00010000, 
B10110001, B01010000,  
B10010000, B10010000, 
B10101000, B00010000, 
B11111111, B11110000, 
B00000000, B00000000, 
B00000000, B00000000, 
B00000000, B00000000, 
B00000000, B00000000, 
B00000000, B00000000,  
B00000000, B00000000, 
B00000000, B00000000, 
B00000000, B00000000, 
B00000000, B00000000,
};

static const unsigned char PROGMEM food[] ={
B00000000, B10000000, 
B00000001, B11100000, 
B00000011, B11111000,  
B00000001, B11111100, 
B00000000, B11111100, 
B00000000, B11111000, 
B00000001, B11110000, 
B00000011, B11100000, 
B00000111, B11000000, 
B00001111, B10000000, 
B00000111, B00000000,  
B00000000, B00000000, 
B00000000, B00000000, 
B00000000, B00000000, 
B00000000, B00000000,
B00000000, B00000000,
};

static const unsigned char PROGMEM room[] ={
B11111111, B11111111,
B11111111, B11111111, 
B11000000, B00001111, 
B11011111, B11101111,  
B11011111, B11101111, 
B11011111, B11101111, 
B11011111, B11101111, 
B11011111, B11101111, 
B11011111, B00101111, 
B11011111, B00101111, 
B11011111, B11101111, 
B11011111, B11101111,  
B11011111, B11101111, 
B11011111, B11101111, 
B11011111, B11101111, 
B11111111, B11111111, 
};

static const unsigned char PROGMEM toilet[] ={
B00000000, B00000000,
B00000000, B00000000, 
B00000000, B00000000, 
B00000000, B00000000,  
B00000000, B00000000, 
B00000000, B00000000, 
B00000000, B00000000, 
B00000000, B00000000, 
B00111111, B00000000, 
B00111111, B00000000, 
B00111111, B00000000, 
B00111111, B00000000,  
B00111111, B10000000, 
B00111111, B11111100, 
B00011111, B11111000, 
B00001111, B11110000,
};

static const unsigned char PROGMEM ball[] ={
B00000000, B00000000, 
B00000000, B00000000, 
B00000000, B00000000,  
B00000000, B00000000, 
B00000000, B00000000, 
B00000000, B00000000, 
B00000000, B00000000, 
B00000000, B00000000, 
B00000000, B00000000, 
B00000111, B11100000, 
B00001111, B11110000,  
B00011111, B11111000, 
B00011111, B11111000, 
B00011111, B11111000, 
B00001111, B11110000,
};

void setup() {
  Serial.begin(9600);
  pinMode(bathroom, INPUT_PULLUP);
  pinMode(feed, INPUT_PULLUP);
  pinMode(stats, INPUT_PULLUP);
  pinMode(play, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x31)
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(6,5);
  display.println("TAMAGOTCHI"); 
  display.display();
  //------------------------------------------------------------------------------------- 
  tone(buzzer, 100);
  delay(75);
  noTone(buzzer);
  tone(buzzer, 200);
  delay(75);
  noTone(buzzer);
  tone(buzzer, 300);
  delay(75);
  noTone(buzzer);
  tone(buzzer, 400);
  delay(75);
  noTone(buzzer);
  tone(buzzer, 500);
  delay(75);
  noTone(buzzer);
  tone(buzzer, 600);
  delay(75);
  noTone(buzzer);
  tone(buzzer, 700);
  delay(75);
  noTone(buzzer);
  tone(buzzer, 800);
  delay(75);
  noTone(buzzer);
  tone(buzzer, 900);
  delay(75);
  noTone(buzzer);
  tone(buzzer, 1000);
  delay(75);
  noTone(buzzer);
  
  delay(1000);  
  //-------------------------------------------------------------------------------------
}

void loop() {
  start:
  int buttonState2 = digitalRead(feed);
  int buttonState3 = digitalRead(bathroom);
  int buttonState1 = digitalRead(stats);
  int buttonState4 = digitalRead(play);
  //-------------------------------------------------------------------------------------
  if (value == 3 ) {
    value = 0;
    hunger = 0;
    happiness = 24;
    restroom = 0;
  }
  //-------------------------------------------------------------------------------------
  if (Display == 1)
  {
    display.clearDisplay();
    display.drawBitmap(55, 15, dino, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
    display.drawBitmap(1, 15, tree, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
    display.drawBitmap(110, 15, tree, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
    display.drawBitmap(21, 15, tree, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
    display.drawBitmap(89, 15, tree, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
    display.drawBitmap(110, 1, sun, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
    display.drawBitmap(1, 1, cloud, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
    display.drawBitmap(40, 1, cloud, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
    display.drawBitmap(80, 1, cloud, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color
    display.display();
  }
  //-------------------------------------------------------------------------------------
  if (buttonState1 == LOW)
  {
    tone(buzzer, 1000);
    delay(75);
    noTone(buzzer);
    Stats();
  }

  if (buttonState2 == LOW)
  {
    tone(buzzer, 1000);
    delay(75);
    noTone(buzzer);
    Feed();
  }

  if (buttonState3 == LOW)
  {
    tone(buzzer, 1000);
    delay(75);
    noTone(buzzer);
    Poop();
  }

  if (buttonState4 == LOW)
  {
    tone(buzzer, 1000);
    delay(75);
    noTone(buzzer);
    Play();
  }
  //-------------------------------------------------------------------------------------
  if (hunger == 24) {
  value++;
  }

  if (happiness == 0) {
   value++;
  }

  if (restroom == 24) {
    value++;
  }
  //-------------------------------------------------------------------------------------
  if (value == 3) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(15,10);
    display.println("I DIED");
    display.display();
    display.clearDisplay();
    delay(1000);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(15,10);
    display.println("I DIED");
    display.display();
    display.clearDisplay();
    delay(1000);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(15,10);
    display.println("I DIED");
    display.display();
  }
  //-------------------------------------------------------------------------------------
  if (restroom == -1) {
    restroom++;
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10,10);
    display.println("I Dont Need To");
    display.display(); 
    delay(1550);
  }

  if (hunger == -1) {
    hunger++;
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10,10);
    display.println("I'm Full");
    display.display(); 
    delay(1550);
  }

  if (happiness == 25) {
    happiness--;
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10,10);
    display.println("I Dont Want To Play");
    display.display(); 
    delay(1550);
  }
  //-------------------------------------------------------------------------------------
  currentMillis = millis(); // get current time
  if (currentMillis - previousMillis >= interval) { // time for action?
    hunger++;
    restroom++;
    happiness--;
    tone(buzzer, 1000);      // Send 1KHz sound signal...
    delay(500);              // ...for 1 sec
    noTone(buzzer);          // Stop sound...
    delay(500);   
    tone(buzzer, 1000);      // Send 1KHz sound signal...
    delay(500);              // ...for 1 sec
    noTone(buzzer);          // Stop sound...
    delay(500);
    previousMillis = currentMillis; // start new period
  }
//-------------------------------------------------------------------------------------
  if (ON == 1)
  {
    currentMillis2 = millis(); // get current time
    if (currentMillis2 - previousMillis2 >= interval2) { // time for action?
      display.clearDisplay();
      display.display(); 
      /*tone(buzzer, 1000);      // Send 1KHz sound signal...
      delay(500);              // ...for 1 sec
      noTone(buzzer);*/ 
      Display--;
      ON--;
      //previousMillis2 = currentMillis2; // start new period
      goto start;
    }
  }
  //-------------------------------------------------------------------------------------
   if (ON ==2)
   {
    ON--;
   }

   if (Display == 2)
   {
    Display--;
   }
  //-------------------------------------------------------------------------------------
}

void Stats()
{
  Display++;
  ON++;
  previousMillis2 = currentMillis2; // start new period
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(1,1);
  display.println("hunger:"); 
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(43,1);
  display.println(hunger); 
  display.display();
  //-----------------------------
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(1,10);
  display.println("happiness:"); 
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(59,10);
  display.println(happiness); 
  display.display();
  //-----------------------------
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(1,20);
  display.println("restroom:");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(55,20);
  display.println(restroom);  
  display.display();
  //-----------------------------
  delay(2550);
}

void Feed()
{
  Display++;
  ON++;
  previousMillis2 = currentMillis2; // start new period

  hunger--;
  display.clearDisplay();
  display.drawBitmap(10, 15, chair, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.drawBitmap(100, 15, lamp, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.drawBitmap(55, 15, dino, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.drawBitmap(20, 10, ptg, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color
  display.drawBitmap(30, 15, food, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color
  display.display();
  delay(1000);
  display.drawBitmap(30, 15, food, 16, 16, BLACK); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color
  display.drawBitmap(34, 17, food, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color
  display.display();
  delay(1000);
  display.drawBitmap(34, 17, food, 16, 16, BLACK); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color
  display.drawBitmap(36, 18, food, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color
  delay(1000);
  display.drawBitmap(36, 18, food, 16, 16, BLACK); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color
  delay(1000);
  display.display();
}

void Poop()
{
  Display++;
  ON++;
  previousMillis2 = currentMillis2; // start new period
  
  restroom--;
  display.clearDisplay();
  display.drawBitmap(55, 15, dino, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.drawBitmap(10, 15, room, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();
  delay(1);
  display.drawBitmap(55, 15, dino, 16, 16, BLACK); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();
  delay(1);
  display.drawBitmap(45, 15, dino, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();
  delay(1);
  display.drawBitmap(45, 15, dino, 16, 16, BLACK); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();
  delay(1);
  display.drawBitmap(35, 15, dino, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();
  delay(1);
  display.drawBitmap(35, 15, dino, 16, 16, BLACK); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();
  delay(1);
  display.drawBitmap(27, 15, dino, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();
  delay(1000);
  display.clearDisplay();
  display.drawBitmap(55, 15, dino, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.drawBitmap(25, 15, toilet, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();
  delay(2000);
  display.clearDisplay();
  display.drawBitmap(55, 15, dino, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.drawBitmap(10, 15, room, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();
  delay(2550);
}

void Play()
{
  Display++;
  ON++;
  previousMillis2 = currentMillis2; // start new period
  
  happiness++;
  display.clearDisplay();
  display.drawBitmap(55, 15, dino, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.drawBitmap(55, 4, ball, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();
  delay(1500);
  display.drawBitmap(55, 4, ball, 16, 16, BLACK); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.drawBitmap(55, 0, ball, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();
  delay(1500);
  display.drawBitmap(55, 4, ball, 16, 16, BLACK); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.drawBitmap(55, 0, ball, 16, 16, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();
  delay(1000);
}
