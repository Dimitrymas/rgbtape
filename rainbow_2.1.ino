#define PIN 13        // пин DI светодиодной ленты (управление)
#define NUM_LEDS 60   // число диодов
#include "Adafruit_NeoPixel.h"

int val;
int LED = 12;
bool STOPLED = false;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void _delay(int waitmil){
  for (int i = 0; i < waitmil; i++) {
    if (Serial.available()) {
      int s = Serial.read();
      if (s == '!') {
        STOPLED = true;
        return;
      }
      
    }
    delay(1);
  }
}

void setup()
{
  strip.begin();
  strip.setBrightness(150);    // яркость, от 0 до 255
  strip.clear();                          // очистить
  strip.show();                           // отправить на ленту
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);

}

void doHelp()
{
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(200);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(200);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(200);
  digitalWrite(LED, LOW);

  Serial.println("send string to play: "); // печатаем помощь
  Serial.println("! - STOP"); 
  Serial.println("0 - fill LED to black");
  Serial.println("1 - fill LED to red");
  Serial.println("2 - fill LED to green");
  Serial.println("3 - fill LED to blue");
  Serial.println("4 - fill LED to red/green/blue");
  Serial.println("5 - color wave (19 times)");
  Serial.println("6 - forward black LED (delay 30)");
  Serial.println("7 - forward red LED (delay 30)");
  Serial.println("8 - forward green LED (delay 30)");
  Serial.println("9 - forward blue LED (delay 30)");
  Serial.println("a - backward black LED (delay 30)");
  Serial.println("b - backward red LED (delay 30)");
  Serial.println("c - backward green LED (delay 30)");
  Serial.println("d - backward blue LED (delay 30)");

}


int getBright(int n) {
  double y = 0;
  if (n < 6 && n >= 0) {
    y = 50 * n;
  }
  if (n < 15  && n >= 6) {
    y = -20 * n + 300;

  }
  if (n > 14) {
    y = -2 * n + 58;
    if (y < 0) {
      y = 0;
    }

  }
  if (n > 30) {
    y = 0;

  }

  return y;
}

void doPlay(int mode) {
  STOPLED = false;
  Serial.print("set mode: "); // печатаем данные
  Serial.println(mode); // печатаем данные
  switch (mode) {
    case 0:
      // выкл
      for (int i = 0; i < NUM_LEDS; i++ ) {   // всю ленту
        strip.setPixelColor(i, 0x000000);     // залить черным
        strip.show();                         // отправить на ленту
      }
      break;
    case 1:
      // заливаем красным
      for (int i = 0; i < NUM_LEDS; i++ ) {   // всю ленту
        strip.setPixelColor(i, 0xff0000);     // залить красным
        strip.show();                         // отправить на ленту
      }
      break;
    case 2:
      // заливаем зеленым
      for (int i = 0; i < NUM_LEDS; i++ ) {   // всю ленту
        strip.setPixelColor(i, 0x00ff00);     // залить красным
        strip.show();                         // отправить на ленту
      }
      break;
    case 3:
      // заливаем синим
      for (int i = 0; i < NUM_LEDS; i++ ) {   // всю ленту
        strip.setPixelColor(i, 0x00ff00);     // залить красным
        strip.show();                         // отправить на ленту
      }
      break;

     case 4:
      // заливаем трёмя цветами плавно
      for (int i = 0; i < NUM_LEDS / 3 && !STOPLED; i++ ) {   // от 0 до первой трети
        strip.setPixelColor(i, 0xff0000);     // залить красным
        strip.show();                         // отправить на ленту
        _delay(50);
      }
      for (int i = NUM_LEDS / 3; i < NUM_LEDS * 2 / 3 && !STOPLED; i++ ) {   // от 1/3 до 2/3
        strip.setPixelColor(i, 0x00ff00);     // залить зелёным
        strip.show();                         // отправить на ленту
        _delay(50);
      }
      for (int i = NUM_LEDS * 2 / 3; i < NUM_LEDS && !STOPLED; i++ ) {   // от 2/3 до конца
        strip.setPixelColor(i, 0x0000ff);     // залить синим
        strip.show();                         // отправить на ленту
        _delay(50);
      }
      break;

      case 5:
      {
        int a = 1;
        int g = 0;


        for (int h = 1; h < 20 && !STOPLED; h++) {  // раз
          for (int j = NUM_LEDS; j > -15 && !STOPLED; j--) {
            for (int i = 0; i < NUM_LEDS && !STOPLED; i++) {
              strip.setPixelColor(i, strip.Color(getBright(i - j), 0, getBright(i - j)/3 * h/2));
            }
            strip.show();
            _delay(30);
          }
          for (int j = 0; j < NUM_LEDS && !STOPLED; j++ ) {
            for (int i = 0; i < NUM_LEDS && !STOPLED; i++) {
              strip.setPixelColor(i, strip.Color(getBright(i - j), getBright(i - j)/3 * h/2, 0));
            }
            strip.show();
            _delay(30);
          }
        }
      }
      break;
    case 6:
      // выкл
      for (int i = 0; i < NUM_LEDS; i++ ) {   // всю ленту
        strip.setPixelColor(i, 0x000000);     // залить черным с задержкой
        strip.show();
        delay(30);
      }
      break;
    case 7:
      // заливаем красным
      for (int i = 0; i < NUM_LEDS; i++ ) {   // всю ленту
        strip.setPixelColor(i, 0xff0000);     // залить красным с задержкой
        strip.show();
        delay(30);
      }
      break;
    case 8:
      // заливаем зеленым
      for (int i = 0; i < NUM_LEDS; i++ ) {   // всю ленту
        strip.setPixelColor(i, 0x00ff00);     // залить зеленым с задержкой
        strip.show();
        delay(30);
      }
      break;
    case 9:
      // заливаем синим
      for (int i = 0; i < NUM_LEDS; i++ ) {   // всю ленту
        strip.setPixelColor(i, 0x0000ff);     // залить синим с задержкой
        strip.show();
        delay(30);
      }
      break;
      
    case 10:
      // заливаем черным в обратную сторону
      for (int i = NUM_LEDS ; i > 0 ; i--) {   // всю ленту
        strip.setPixelColor(i, 0x000000);     // залить красным с задержкой
        strip.show();
        delay(30);
      }
      break;
    case 11:
      // заливаем красным в обратную сторону
      for (int i = NUM_LEDS ; i > 0 ; i--) {   // всю ленту
        strip.setPixelColor(i, 0xff0000);     // залить красным с задержкой
        strip.show();
        delay(30);
      }
      break;
    case 12:
      // заливаем зеленым в обратную сторону
      for (int i = NUM_LEDS ; i > 0 ; i--) {   // всю ленту
        strip.setPixelColor(i, 0x00ff00);     // залить зеленым с задержкой
        strip.show();
        delay(30);
      }
      break;
    case 13:
      // заливаем синим в обратную сторону
      for (int i = NUM_LEDS ; i > 0 ; i-- ) {   // всю ленту
        strip.setPixelColor(i, 0x0000ff);     // залить синим с задержкой
        strip.show();
        delay(30);
      }
      break;
  }
}


void loop()
{
  if (Serial.available())
  {
    val = Serial.read();
    switch (val) {
      case '0':
        doPlay(0);
        break;
      case '1':
        doPlay(1);
        break;
      case '2':
        doPlay(2);
        break;
      case '3':
        doPlay(3);
        break;
      case '4':
        doPlay(4);
        break;
      case '5':
        doPlay(5);
        break;
      case '6':
        doPlay(6);
        break;
      case '7':
        doPlay(7);
        break;
      case '8':
        doPlay(8);
        break;
      case '9':
        doPlay(9);
        break;
      case 'a':
        doPlay(10);
        break;
      case 'b':
        doPlay(11);
        break;
      case 'c':
        doPlay(12);
        break;
      case 'd':
        doPlay(13);
        break;
      case '?':
        doHelp();
        break; 
    }
  }
}
