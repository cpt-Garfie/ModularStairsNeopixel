#include <FastLED.h>
#define LEDS_PER_PART     30
#define ARROW_WIDTH       2

#define BRIGHTNESS        255

#define NR_OF_STAIR_STEPS 16

#define BOTTOM_SENSOR     6
#define UPPER_SENSOR      7

typedef enum { LEFT = 0, RIGHT, BOTH } runDirectionType;

typedef struct {
  uint8_t hue;
  int runningIndex;
  CRGB* LedArray;
} stair_struct;

typedef struct {
  int startIndex;
  int minIndex;
  int maxIndex;
  int fadeInSpeed;
  int delayNext;
  uint8_t CHSVHue;
  uint8_t CHSVSaturation;
  uint8_t CHSVBrightness;
  uint8_t hueIncrement;
  runDirectionType runDirection;
} pattern_struct;

int iLedsCenter = LEDS_PER_PART / 2;

bool bWalkingDirection = false;

pattern_struct startPattern { iLedsCenter, 0, LEDS_PER_PART, 30, (LEDS_PER_PART / 4 * 3), 0, 255, 255, 2, BOTH };
const pattern_struct fadeOutPattern { 0, 0, LEDS_PER_PART, 20, (LEDS_PER_PART / 4), 0, 0, 0, 0, BOTH };

CRGB LedArray1[LEDS_PER_PART];
CRGB LedArray2[LEDS_PER_PART];
CRGB LedArray3[LEDS_PER_PART];
CRGB LedArray4[LEDS_PER_PART];
CRGB LedArray5[LEDS_PER_PART];
CRGB LedArray6[LEDS_PER_PART];
CRGB LedArray7[LEDS_PER_PART];

CRGB LedArray8[LEDS_PER_PART];
CRGB LedArray9[LEDS_PER_PART];
CRGB LedArray10[LEDS_PER_PART];
CRGB LedArray11[LEDS_PER_PART];
CRGB LedArray12[LEDS_PER_PART];
CRGB LedArray13[LEDS_PER_PART];
CRGB LedArray14[LEDS_PER_PART];
CRGB LedArray15[LEDS_PER_PART];
CRGB LedArray16[LEDS_PER_PART];

volatile stair_struct Stair[NR_OF_STAIR_STEPS] = { 0 };

void runPattern(pattern_struct patternToRun, stair_struct * Stair);
void runArrowOverPattern(stair_struct * Stair);

void setup() {
  // Add the steps to the neopixel class
  FastLED.addLeds<NEOPIXEL, 31>(LedArray1, LEDS_PER_PART);
  FastLED.addLeds<NEOPIXEL, 33>(LedArray2, LEDS_PER_PART);
  FastLED.addLeds<NEOPIXEL, 35>(LedArray3, LEDS_PER_PART);
  FastLED.addLeds<NEOPIXEL, 37>(LedArray4, LEDS_PER_PART);
  FastLED.addLeds<NEOPIXEL, 39>(LedArray5, LEDS_PER_PART);
  FastLED.addLeds<NEOPIXEL, 41>(LedArray6, LEDS_PER_PART);
  FastLED.addLeds<NEOPIXEL, 43>(LedArray7, LEDS_PER_PART);

  FastLED.addLeds<NEOPIXEL, 30>(LedArray8, LEDS_PER_PART);
  FastLED.addLeds<NEOPIXEL, 32>(LedArray9, LEDS_PER_PART);
  FastLED.addLeds<NEOPIXEL, 34>(LedArray10, LEDS_PER_PART);
  FastLED.addLeds<NEOPIXEL, 36>(LedArray11, LEDS_PER_PART);
  FastLED.addLeds<NEOPIXEL, 38>(LedArray12, LEDS_PER_PART);
  FastLED.addLeds<NEOPIXEL, 40>(LedArray13, LEDS_PER_PART);
  FastLED.addLeds<NEOPIXEL, 42>(LedArray14, LEDS_PER_PART);
  FastLED.addLeds<NEOPIXEL, 44>(LedArray15, LEDS_PER_PART);
  FastLED.addLeds<NEOPIXEL, 46>(LedArray16, LEDS_PER_PART);

  // Initialize the stair structure
  Stair[0].LedArray = LedArray1;
  Stair[1].LedArray = LedArray2;
  Stair[2].LedArray = LedArray3;
  Stair[3].LedArray = LedArray4;
  Stair[4].LedArray = LedArray5;
  Stair[5].LedArray = LedArray6;
  Stair[6].LedArray = LedArray7;

  Stair[7].LedArray = LedArray8;
  Stair[8].LedArray = LedArray9;
  Stair[9].LedArray = LedArray10;
  Stair[10].LedArray = LedArray11;
  Stair[11].LedArray = LedArray12;
  Stair[12].LedArray = LedArray13;
  Stair[13].LedArray = LedArray14;
  Stair[14].LedArray = LedArray15;
  Stair[15].LedArray = LedArray16;

  if (LEDS_PER_PART % 2) {
    iLedsCenter++;
  }

  pinMode(BOTTOM_SENSOR, INPUT);
  pinMode(UPPER_SENSOR, INPUT);
  FastLED.setBrightness(  BRIGHTNESS );

  Serial.begin(9600);
}

void loop() {
  if (digitalRead(BOTTOM_SENSOR)) {
    bWalkingDirection = false;
    runPattern(startPattern, Stair);
    runArrowOverPattern(Stair);
    runArrowOverPattern(Stair);
    runArrowOverPattern(Stair);
    delay(2000);
    runPattern(fadeOutPattern, Stair);
  }
  else if (digitalRead(UPPER_SENSOR)) {
    bWalkingDirection = true;
    runPattern(startPattern, Stair);
    runArrowOverPattern(Stair);
    runArrowOverPattern(Stair);
    runArrowOverPattern(Stair);
    delay(2000);
    runPattern(fadeOutPattern, Stair);
  }
  else {
    // do nothing
  }

  startPattern.CHSVHue += LEDS_PER_PART * 2;
}

void runPattern(pattern_struct patternToRun, stair_struct * Stair) {
  // Walking down the stairs
  if (bWalkingDirection) {
    Serial.println("Down the stairs!");
    switch (patternToRun.runDirection) {
      case LEFT:

        break;

      case RIGHT:

        break;

      case BOTH:
        {
          // Set all runningIndexes and hues to the default of the pattern.
          for (int iStep = 0; iStep < NR_OF_STAIR_STEPS; iStep++) {
            Stair[iStep].runningIndex = patternToRun.startIndex;
            Stair[iStep].hue = patternToRun.CHSVHue;
          }

          int j = Stair[NR_OF_STAIR_STEPS - 1].runningIndex;
          int iRunningSteps = NR_OF_STAIR_STEPS - 2;  // If NR_OF_STAIR_STEPS were 8, an array only counts to 7 (so -1) but we want the for loop below to at least run 1 time, that makes it -2

          // Keep this pattern running until the last step of the stair has reached the end of the animation
          while (Stair[0].runningIndex < patternToRun.maxIndex) {
            // Simultanously running the animations per step of the stairs.
            for (int i = NR_OF_STAIR_STEPS - 1; i >= iRunningSteps; i--) {
              // Only run the steps which aren't done animating
              if (Stair[i].runningIndex < patternToRun.maxIndex) {
                if (i == 0) {
                  Serial.print("Hue step 1: ");
                  Serial.println(Stair[i].hue);
                }
                Stair[i].LedArray[Stair[i].runningIndex] = CHSV(Stair[i].hue, patternToRun.CHSVSaturation, patternToRun.CHSVBrightness);
                Stair[i].LedArray[patternToRun.maxIndex - 1 - Stair[i].runningIndex] = CHSV(Stair[i].hue, patternToRun.CHSVSaturation, patternToRun.CHSVBrightness);
                Stair[i].hue += patternToRun.hueIncrement;
                Stair[i].runningIndex++;
              }
            }

            // Depending on the delay we have issued in the delayNext variable in the pattern struct, we will increment j and iRunningsteps.
            if (j < patternToRun.maxIndex || j > patternToRun.minIndex) {
              j++;
              if ( j >= patternToRun.delayNext && iRunningSteps > 0 ) {
                iRunningSteps--;
                j = Stair[iRunningSteps].runningIndex;
              }
            }

            // Determine the speed of the animation.
            FastLED.delay(patternToRun.fadeInSpeed);
          }

          Serial.println("Pattern Finished!");
        }
        break;
    }
  }
  // walking up the stairs
  else {
    Serial.println("Up the stairs!");
    switch (patternToRun.runDirection) {
      case LEFT:

        break;

      case RIGHT:

        break;

      case BOTH:
        {
          // Set all runningIndexes and hues to the default of the pattern.
          for (int iStep = 0; iStep < NR_OF_STAIR_STEPS; iStep++) {
            Stair[iStep].runningIndex = patternToRun.startIndex;
            Stair[iStep].hue = patternToRun.CHSVHue;
          }

          int j = Stair[0].runningIndex;
          int iRunningSteps = 1;

          // Keep this pattern running until the last step of the stair has reached the end of the animation
          while (Stair[NR_OF_STAIR_STEPS - 1].runningIndex < patternToRun.maxIndex) {
            // Simultanously running the animations per step of the stairs.
            for (int i = 0; i < iRunningSteps; i++) {
              // Only run the steps which aren't done animating
              if (Stair[i].runningIndex < patternToRun.maxIndex) {
                if (i == 0) {
                  Serial.print("Hue step 1: ");
                  Serial.println(Stair[i].hue);
                }
                Stair[i].LedArray[Stair[i].runningIndex] = CHSV(Stair[i].hue, patternToRun.CHSVSaturation, patternToRun.CHSVBrightness);
                Stair[i].LedArray[patternToRun.maxIndex - 1 - Stair[i].runningIndex] = CHSV(Stair[i].hue, patternToRun.CHSVSaturation, patternToRun.CHSVBrightness);
                Stair[i].hue += patternToRun.hueIncrement;
                Stair[i].runningIndex++;
              }
            }

            // Depending on the delay we have issued in the delayNext variable in the pattern struct, we will increment j and iRunningsteps.
            if (j < patternToRun.maxIndex || j > patternToRun.minIndex) {
              j++;
              if ( j >= patternToRun.delayNext && iRunningSteps < NR_OF_STAIR_STEPS ) {
                iRunningSteps++;
                j = Stair[iRunningSteps - 1].runningIndex;
              }
            }

            // Determine the speed of the animation.
            FastLED.delay(patternToRun.fadeInSpeed);
          }

          Serial.println("Pattern Finished!");
        }
        break;
    }
  }
}

void runArrowOverPattern(stair_struct * Stair) {
  Serial.println("Arrow!");
  // Set all runningIndexes to the start index of the pattern.
  for (int iStep = 0; iStep < NR_OF_STAIR_STEPS; iStep++) {
    Stair[iStep].runningIndex = iLedsCenter;
  }
  // Walking down the stairs
  if (bWalkingDirection) {
    int j = Stair[NR_OF_STAIR_STEPS - 1].runningIndex;
    int iRunningSteps = NR_OF_STAIR_STEPS - 2;

    // Keep this pattern running until the last step of the stair has reached the end of the animation
    while (Stair[0].runningIndex < LEDS_PER_PART) {
      // Simultanously running the animations per step of the stairs.
      for (int i = NR_OF_STAIR_STEPS - 1; i > iRunningSteps; i--) {
        // Only run the steps which aren't done animating
        if (Stair[i].runningIndex < LEDS_PER_PART) {
          if (i == 0) {
            Serial.print("Hue step 1: ");
            Serial.println(Stair[i].hue);
          }
          Stair[i].LedArray[Stair[i].runningIndex] = CHSV(0, 0, 240);
          if (LEDS_PER_PART % 2 && Stair[i].runningIndex == iLedsCenter) {
            Stair[i].LedArray[LEDS_PER_PART - 1 - Stair[i].runningIndex + 1] =  CHSV(0, 0, 240);
          }
          else {
            Stair[i].LedArray[LEDS_PER_PART - 1 - Stair[i].runningIndex] =  CHSV(0, 0, 240);
          }
          Stair[i].runningIndex++;
        }

        if (Stair[i].runningIndex >= LEDS_PER_PART) {
          // Last part to erase
          for (int erase = ARROW_WIDTH; erase >= 0; erase--) {
            Stair[i].LedArray[erase] = CHSV(Stair[i].hue, 255, 255);
            Stair[i].LedArray[LEDS_PER_PART - 1 - erase] = Stair[i].LedArray[erase];
          }
        }
        else if (Stair[i].runningIndex > iLedsCenter + (ARROW_WIDTH - 1)) {
          int j = Stair[i].runningIndex - ARROW_WIDTH;
          Stair[i].LedArray[j - 1] = CHSV(Stair[i].hue, 255, 255);
          if (LEDS_PER_PART % 2 && j == iLedsCenter) {
            Stair[i].LedArray[LEDS_PER_PART - j + 1] = CHSV(Stair[i].hue, 255, 255);
          }
          else {
            Stair[i].LedArray[LEDS_PER_PART - j] = CHSV(Stair[i].hue, 255, 255);
          }
        }
      }

      // Depending on the delay we have issued in the delayNext variable in the pattern struct, we will increment j and iRunningsteps.
      if (j < LEDS_PER_PART) {
        j++;
        if ( j >= LEDS_PER_PART / 2 + ARROW_WIDTH && iRunningSteps >= 0 ) {
          iRunningSteps--;
          j = Stair[iRunningSteps].runningIndex;
        }
      }

      // Determine the speed of the animation.
      FastLED.delay(50);
    }
  }
  // walking up the stairs
  else {
    int j = Stair[0].runningIndex;
    int iRunningSteps = 1;

    // Keep this pattern running until the last step of the stair has reached the end of the animation
    while (Stair[NR_OF_STAIR_STEPS - 1].runningIndex < LEDS_PER_PART) {
      // Simultanously running the animations per step of the stairs.
      for (int i = 0; i < iRunningSteps; i++) {
        // Only run the steps which aren't done animating
        if (Stair[i].runningIndex < LEDS_PER_PART) {
          if (i == 0) {
            Serial.print("Hue step 1: ");
            Serial.println(Stair[i].hue);
          }
          Stair[i].LedArray[Stair[i].runningIndex] = CHSV(0, 0, 240);
          if (LEDS_PER_PART % 2 && Stair[i].runningIndex == iLedsCenter) {
            Stair[i].LedArray[LEDS_PER_PART - 1 - Stair[i].runningIndex + 1] =  CHSV(0, 0, 240);
          }
          else {
            Stair[i].LedArray[LEDS_PER_PART - 1 - Stair[i].runningIndex] =  CHSV(0, 0, 240);
          }
          Stair[i].runningIndex++;
        }

        if (Stair[i].runningIndex >= LEDS_PER_PART) {
          // Last part to erase
          for (int erase = ARROW_WIDTH; erase >= 0; erase--) {
            Stair[i].LedArray[erase] = CHSV(Stair[i].hue, 255, 255);
            Stair[i].LedArray[LEDS_PER_PART - 1 - erase] = Stair[i].LedArray[erase];
          }
        }
        else if (Stair[i].runningIndex > iLedsCenter + (ARROW_WIDTH - 1)) {
          int j = Stair[i].runningIndex - ARROW_WIDTH;
          Stair[i].LedArray[j - 1] = CHSV(Stair[i].hue, 255, 255);
          if (LEDS_PER_PART % 2 && j == iLedsCenter) {
            Stair[i].LedArray[LEDS_PER_PART - j + 1] = CHSV(Stair[i].hue, 255, 255);
          }
          else {
            Stair[i].LedArray[LEDS_PER_PART - j] = CHSV(Stair[i].hue, 255, 255);
          }
        }
      }

      // Depending on the delay we have issued in the delayNext variable in the pattern struct, we will increment j and iRunningsteps.
      if (j < LEDS_PER_PART) {
        j++;
        if ( j >= LEDS_PER_PART / 2 + ARROW_WIDTH && iRunningSteps < NR_OF_STAIR_STEPS ) {
          iRunningSteps++;
          j = Stair[iRunningSteps - 1].runningIndex;
        }
      }

      // Determine the speed of the animation.
      FastLED.delay(50);
    }
  }
  Serial.println("Pattern Finished!");
}
