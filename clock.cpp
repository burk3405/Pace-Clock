#include <LedControl.h>

// MAX7219 wiring (DIN, CLK, CS)
LedControl lc = LedControl(11, 13, 10, 1);

unsigned long lastTick = 0;
int seconds = 0;
int minutes = 0;

void setup() {
  lc.shutdown(0, false);   // Wake up MAX7219
  lc.setIntensity(0, 8);   // Brightness (0–15)
  lc.clearDisplay(0);      // Clear display
}

void loop() {
  unsigned long now = millis();
  if (now - lastTick >= 1000) {  // every second
    lastTick = now;
    seconds++;

    if (seconds >= 60) {
      seconds = 0;
      minutes++;
      if (minutes >= 60) minutes = 0;  // reset every hour
    }

    displayTime(minutes, seconds);
  }
}

void displayTime(int m, int s) {
  // Display as MM:SS
  int mTens = m / 10;
  int mOnes = m % 10;
  int sTens = s / 10;
  int sOnes = s % 10;

  lc.setDigit(0, 3, mTens, false);
  lc.setDigit(0, 2, mOnes, true);  // colon simulated with decimal point
  lc.setDigit(0, 1, sTens, false);
  lc.setDigit(0, 0, sOnes, false);
}
