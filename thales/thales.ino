#include <Keypad.h>

/*
-----------------
| 1 | 2 | 3 | F |
-----------------
| 4 | 5 | 6 | E |
-----------------
| 7 | 8 | 9 | D |
-----------------
| A | 0 | B | C |
-----------------
| | | | |  |  |  |
| | | | |  |  |  |
9 8 7 6 13 12 11 10
*/

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
    {'1','2','3', 'F'},
    {'4','5','6', 'E'},
    {'7','8','9', 'D'},
    {'A','0','B', 'C'}
};

byte colPins[COLS] = { 13, 12, 11, 10 };
byte rowPins[ROWS] = { 9, 8, 7, 6 };

Keypad kpd = Keypad( makeKeymap(keys), colPins, rowPins, ROWS, COLS );

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    char key = kpd.getKey();
    if(key)
        Serial.print(key);
}
