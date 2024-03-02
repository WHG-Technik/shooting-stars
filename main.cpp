#include<DMXSerial.h>
#include <FastLED.h>
#define NUM_LEDS 8
#define DATA_PIN 2
#define DMX_Start 1
#define shooting_star_anzahl 5

int tick_count = 0;

//int dmx_values[shooting_star_anzahl*4];
int dmx_values[] = {120,255,0,0,120,255,0,0,120,255,0,0,120,255,0,0,120,255,0,0};
int led_states[shooting_star_anzahl];

CRGB leds[NUM_LEDS];

void setup() {
    //Serial.begin(9600);
    DMXSerial.init(DMXReceiver);
    FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
    for (int i=0; i<shooting_star_anzahl; i++) {
        led_states[i] = 0;
    }
}

void loop() {
    /*
      for(int c = 0; c < shooting_star_anzahl*4; c++){
        int dmx_value = DMXSerial.read(DMX_Start + c);
        if (dmx_value > 0) {

          // First addr is interval
          if (c % 4 == 0) {
            dmx_values[c] = abs(255-dmx_value);
          } else {
            dmx_values[c] = dmx_value;
          }
        }
      }
    */

    for (int i=0; i<shooting_star_anzahl; i++) {
        if (tick_count % dmx_values[i*4] == 0) {
            int state = led_states[i];
            if (state-3 < 0) {
                leds[state] = CRGB(dmx_values[i*4+1], dmx_values[i*4+2], dmx_values[i*4+3]);
                FastLED.show();
            } else {
                for (int c=0; c<state-3; c++) {
                    leds[c] = CRGB::Black;
                    FastLED.show();
                }
                for (int c=state-3; c<state; c++) {
                    leds[c] = CRGB(dmx_values[i*4+1], dmx_values[i*4+2], dmx_values[i*4+3]);
                    FastLED.show();
                }
            }
            if (state >= NUM_LEDS-1) {
                led_states[i] = 0;
            } else {
                led_states[i] = state+1;
            }
        }
    }

    delay(1);
    tick_count++;

}