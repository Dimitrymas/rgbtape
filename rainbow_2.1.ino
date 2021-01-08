#define PIN 13        // пин DI
#define NUM_LEDS 60   // число диодов
#include "Adafruit_NeoPixel.h"
#include "IRremote.h"
int ledmode = 0;
IRrecv irrecv(2); // указываем вывод, к которому подключен приемник

decode_results results;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

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
  Serial.println(mode); // печатаем данные
  switch (mode) {
    case 1:
      // заливаем красным
      for (int i = 0; i < NUM_LEDS; i++ ) {   // всю ленту
        strip.setPixelColor(i, 0xff0000);     // залить белым
        strip.show();                         // отправить на ленту
        delay(30);
      }
      break;
    case 0:
      // заливаем черным
      for (int i = 0; i < NUM_LEDS; i++ ) {   // всю ленту
        strip.setPixelColor(i, 0x000000);     // залить белым
        strip.show();                         // отправить на ленту
        delay(30);
      }
      break;
    case 2:
      // заливаем трёмя цветами плавно
      for (int i = 0; i < NUM_LEDS / 3; i++ ) {   // от 0 до первой трети
        strip.setPixelColor(i, 0xff0000);     // залить красным
        strip.show();                         // отправить на ленту
        delay(100);
      }
      for (int i = NUM_LEDS / 3; i < NUM_LEDS * 2 / 3; i++ ) {   // от 1/3 до 2/3
        strip.setPixelColor(i, 0x00ff00);     // залить зелёным
        strip.show();                         // отправить на ленту
        delay(100);
      }
      for (int i = NUM_LEDS * 2 / 3; i < NUM_LEDS; i++ ) {   // от 2/3 до конца
        strip.setPixelColor(i, 0x0000ff);     // залить синим
        strip.show();                         // отправить на ленту
        delay(100);
      }
      delay(1000);
      // заливаем белым
      for (int i = 0; i < NUM_LEDS; i++ ) {   // всю ленту
        strip.setPixelColor(i, 0xffffff);     // залить белым
        strip.show();                         // отправить на ленту
        delay(10);
      }
      delay(1000);
      // заливаем чёрным
      for (int i = 0; i < NUM_LEDS; i++ ) {   // всю ленту
        strip.setPixelColor(i, 0x000000);     // залить чёрным
        strip.show();                         // отправить на ленту
        delay(10);
      }
      delay(1000);
      strip.setPixelColor(NUM_LEDS - 1, 0xffff00);
      strip.show();
      // включаем случайные диоды жёлтым
      for (int i = 0; i < 150; i++ ) {         // 600 раз
        strip.setPixelColor(random(0, NUM_LEDS - 1), 0xffff00);   // залить жёлтым
        strip.show();                         // отправить на ленту
        delay(50);
      }

      break;


    case 4:
      // заливаем трёмя цветами плавно
      for (int i = 0; i < NUM_LEDS / 3; i++ ) {   // от 0 до первой трети
        strip.setPixelColor(i, 0xff0000);     // залить красным
        strip.show();                         // отправить на ленту
        delay(100);
      }
      for (int i = NUM_LEDS / 3; i < NUM_LEDS * 2 / 3; i++ ) {   // от 1/3 до 2/3
        strip.setPixelColor(i, 0x00ff00);     // залить зелёным
        strip.show();                         // отправить на ленту
        delay(100);
      }
      for (int i = NUM_LEDS * 2 / 3; i < NUM_LEDS; i++ ) {   // от 2/3 до конца
        strip.setPixelColor(i, 0x0000ff);     // залить синим
        strip.show();                         // отправить на ленту
        delay(100);
      }
      break;
    case 5:
      {
        int a = 1;
        int g = 0;

        for (int h = 1; h < 20 ; h++) {  // всю ленту
          for (int j = NUM_LEDS; j > -15 ; j--) {  // всю ленту
            for (int i = 0; i < NUM_LEDS; i++) {   // всю ленту
              strip.setPixelColor(i, strip.Color(getBright(i - j), 0, getBright(i - j)/3 * h/2));
            }
            strip.show();
            delay(30);
          }
          for (int j = 0; j < NUM_LEDS ; j++ ) { // всю ленту
            for (int i = 0; i < NUM_LEDS; i++) {   // всю ленту
              strip.setPixelColor(i, strip.Color(getBright(i - j), getBright(i - j)/3 * h/2, 0));
            }
            strip.show();
            delay(30);
          }
        }

      }
      break;
  }
}

void setup() {
  strip.begin();
  strip.setBrightness(150);    // яркость, от 0 до 255
  strip.clear();                          // очистить
  strip.show();                           // отправить на ленту
  Serial.begin(9600); // выставляем скорость COM порта
  irrecv.enableIRIn(); // запускаем прием
}
void loop() {
  if ( irrecv.decode( &results )) { // если данные пришли
    Serial.println( results.value, HEX ); // печатаем данные
    switch ( results.value ) {
      case 0x73FA847B: //нажали 1
        ledmode = 1;

        break;
      case 0x73FA04FB: //нажали 0
        ledmode = 0;

        break;
      case 0x73FA44BB://нажали 2
        ledmode = 2;

        break;
      case 0x73FAC43B: //нажали 3
        ledmode = 4;
        break;
      case 0x73FA24DB: //нажали 4
        ledmode = 5;
        break;
    }
    doPlay(ledmode);
    irrecv.resume(); // принимаем следующую команду
  }

}
