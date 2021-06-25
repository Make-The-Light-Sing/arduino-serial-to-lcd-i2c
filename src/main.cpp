#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define MAXLENGTH 20;

LiquidCrystal_I2C lcd(0x3F, 20, 4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

String line1, line2, line3, line4 = "";

void updateScreen(String newMessage);
String _readSerial();

void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.noBacklight();
  lcd.clear();
  lcd.setCursor(0,0);
  Serial.begin(9600);
}

void loop()
{
    String buffer = _readSerial();
    if (buffer.length() > 0) {
        updateScreen(buffer);
    }
}

/**
 * Update string adding a new line with the new message at the end
 * @param String
 */
void updateScreen(String newMessage) {
    line1 = line2;
    line2 = line3;
    line3 = line4;
    line4 = newMessage;

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(line1);
    lcd.setCursor(0,1);
    lcd.print(line2);
    lcd.setCursor(0,2);
    lcd.print(line3);
    lcd.setCursor(0,3);
    lcd.print(line4);
}

String _readSerial() {
    String buffer = "";
    char lastChar = 0;

    while(buffer.length() < 20) {
        while (Serial.available() > 0) {
            char readChar = Serial.read();
            if (readChar == '\n' || readChar == '\r') {
                return buffer;
            }
            if (readChar >= 32) {
                buffer.concat(readChar);
            }
            if (buffer.length() >= 20) {
                return buffer;
            }
        }
        delay(100);
    }
    return buffer;
}