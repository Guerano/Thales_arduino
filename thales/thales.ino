#include <Keypad.h>
#include <Wire.h>  // Comes with Arduino IDE
#include "/home/guerano/Documents/arduino/thales/thales/music.cc"

#include <LiquidCrystal_PCF8574.h>
LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int show;

#include "wifi_wpa.h"

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
 | |  |  |  | | | |
 | |  |  |  | | | |
13 12 11 10 9 8 7 6
*/

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
    {'1','2','3', 'F'},
    {'4','5','6', 'E'},
    {'7','8','9', 'D'},
    {'A','0','B', 'C'}
};

byte rowPins[ROWS] = { 13, 12, 11, 10 };
byte colPins[COLS] = { 9, 8, 7, 6 };

Keypad kpd = Keypad( makeKeymap(keys), colPins, rowPins, ROWS, COLS );

char ssid[] = "You Shall Not Connect";
char pass[] = "12345678910";

Song zelda("Song of Storm", 500);
Sound key_sound(DO, NOIRE);

void setup()
{
    int error = 0;

    Serial.begin(9600);
    //Serial.println("Trying to connect to `You Shall Not Connect`...");
    //int res = connect(ssid, pass, 1);
    //Serial.println(res);
    Wire.begin();
    Wire.beginTransmission(0x27);
    error = Wire.endTransmission();
    Serial.print("Error: ");
    Serial.print(error);

    if (error == 0) {
      Serial.println(": LCD found.");
    } else {
      Serial.println(": LCD not found.");
    } // if

    pinMode(speakerPin, OUTPUT);
    zelda.create(0,
//#include "/home/guerano/Documents/arduino/thales/songs/song_of_storms.def"
#include "/home/guerano/Documents/arduino/thales/songs/treasure_chest.def"
);
    zelda.play();
    /*potc.create(0,
#include "/home/guerano/Documents/arduino/thales/songs/hes_a_pirate.def"
);*/

    lcd.begin(16, 2); // initialize the lcd
    lcd.setBacklight(255);
    lcd.home();
    setup_enter_password();
}

char input[16] = { 0 };
char flags[] = "53256987";
int curr = 0;

void setup_enter_password()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Password?");
  lcd.setCursor(0,1);
  lcd.blink();
  for (int i = 0; i < sizeof (input); ++i)
    input[i] = 0;
  curr = 0;
}

int check_password()
{
  lcd.noBlink();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Verifying");
  for (int i = 0; i < 2; ++i)
  {
    lcd.setCursor(9, 0);
    lcd.print("   ");
    lcd.setCursor(9, 0);
    for (int j = 0; j < 3; ++j)
    {
      delay(500);
      lcd.print(".");
    }
    delay(1000);
  }
  lcd.clear();
  int i = 0;
  for (i = 0; flags[i] && input[i]; ++i)
    if (flags[i] != input[i])
      break;
  lcd.setCursor(0,0);
  if (flags[i] != input[i])
  {
     lcd.print("Failed");
     return 0;
  }
  lcd.setCursor(0,0);
  lcd.print("Success");
  zelda.play();
  return 1;
}

void loop()
{
    char key = kpd.getKey();
    if(key)
    {
        key_sound.playSound(key_sound.get_beat() / 6 * 300);
        Serial.print(key);
        if (key == 'B') // end of input
        {
          if (!check_password())
          {
            // TODO take a picture
          }
          delay(1000);
          setup_enter_password();
        }
        else if (key == 'C')
        {
          input[curr] = '\0';
          if (curr > 0)
            --curr;
          lcd.setCursor(curr, 1);
          lcd.print(' ');
          lcd.setCursor(curr, 1);
        }
        else if (curr < sizeof (input) - 1)
        {
          lcd.print("*");
          input[curr++] = key;
        }
    }
}
