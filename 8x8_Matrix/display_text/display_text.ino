
#include "font8x8.h"


const int ROW_PINS[] = {6, 7, 8, 9, 10, 11, 12, 13};
const int COL_PINS[] = {A3, A2, A1, A0, 2, 3, 4, 5};

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(ROW_PINS[i], OUTPUT);
    pinMode(COL_PINS[i], OUTPUT);
  }
}

void loop() {
  display_text(L"Andréia" L"\xA9");
}

void clear_display() {
  for (int i = 0; i < 8; i++) {
    digitalWrite(ROW_PINS[i], LOW);
    digitalWrite(COL_PINS[i], HIGH);
  }
}

void display_text(const wchar_t *chr) {
  for (const wchar_t *c = chr;
       *c != '\0';
       display_char(*c++))
    ;
}

void display_char(const wchar_t chr) {
  display_bitmap(get_font(chr));
}

const char * get_font(const wchar_t chr) {
  int i = (int) chr;
  if (0x0000 <= i && i <= 0x007F) return font8x8_basic[i];
  if (0x00A0 <= i && i <= 0x00FF) return font8x8_ext_latin[i - 0x00A0];
  return font8x8_basic[0];
}

void display_bitmap (const char bitmap[8]) {
  for (int i = 0 ; i < 100 ; i++)

    for (int c = 0; c < 8; c++) {
      digitalWrite(COL_PINS[c], LOW);

      for (int r = 0; r < 8; r++)  {
        digitalWrite(ROW_PINS[r], bitmap[r] & 0x01 << c);
      }

      clear_display();
      delay(1);
    }
}
