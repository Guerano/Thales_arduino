// This is a snapshot sketch using the V0C706 library.
// On start, the Arduino will find the camera and then snap a
// photo, first printing the size then the content of the photo
// on the Serial port (Rx, Tx).

#include <Adafruit_VC0706.h>
#include <SoftwareSerial.h>       
  
#include <LiquidCrystal_PCF8574.h>

#include "Arduino.h"
#include "Keypad.h"

/********************
 ****** Others ******
 *******************/

const int myled = 11; // This led will be shining when sending on Serial
const int butt = 8; // Click on the button to send a picture

/********************
 ****** Camera ******
 *******************/

// Using SoftwareSerial (Arduino 1.0+) or NewSoftSerial (Arduino 0023 & prior):
#if ARDUINO >= 100
// On Uno: camera TX connected to pin 2, camera RX to pin 3:
SoftwareSerial cameraconnection = SoftwareSerial(2, 3);
#else
NewSoftSerial cameraconnection = NewSoftSerial(2, 3);
#endif

Adafruit_VC0706 cam = Adafruit_VC0706(&cameraconnection);
bool ok_cam = false;

void setup_cam()
{
  // Try to locate the camera
  if (! cam.begin())
  {
    test_send("No camera found :(");
    return;
  }
  // Set the picture size - you can choose one of 640x480, 320x240 or 160x120 
  // Remember that bigger pictures take longer to transmit!
  //cam.setImageSize(VC0706_640x480);        // biggest
  //cam.setImageSize(VC0706_320x240);        // medium
  cam.setImageSize(VC0706_160x120);          // small
  ok_cam = true;
}

void take_picture()
{
  if (! ok_cam)
    return;

  if (! cam.takePicture()) 
  {
    test_send("Failed to snap!");
    return;
  }
  
  // Get the size of the image (frame) taken  
  uint16_t jpglen = cam.frameLength();
  
  // Read all the data up to # bytes!
  Serial.println(jpglen);
  
  while (jpglen > 0) {
    // read 32 bytes at a time;
    uint8_t *buffer;
    uint8_t bytesToRead = min(32, jpglen); // change 32 to 64 for a speedup but may not work with all setups!
    buffer = cam.readPicture(bytesToRead);
    Serial.write(buffer, bytesToRead);
    jpglen -= bytesToRead;
  }
  Serial.flush();
  // Camera can take pictures again
  cam.resumeVideo();
}

// Simple function that send a string on Serial.
void test_send(String str)
{
  Serial.println(str.length());
  Serial.print(str);
}

/********************
 ******* LCD *******
 *******************/

#define LCD_ADDRESS 0x27

LiquidCrystal_PCF8574 lcd(LCD_ADDRESS); // set the LCD  address to 0x27 for a 16 chars and 2 lines display

char input[16] = { 0 };
char flags[] = "1234567890";
int curr = 0;

void setup_lcd()
{
  /* maybe this is not needed
  Wire.begin();
  Wire.beginTransmission(LCD_ADDRESS);
  */
  lcd.begin(16, 2);
  lcd.setBacklight(255);
    setup_enter_password();
}

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
  int i = 0;
  for (i = 0; flags[i] && input[i]; ++i)
    if (flags[i] != input[i])
      break;
  lcd.setCursor(0,0);
  return flags[i] == input[i];
}

/********************
 ****** Keypad ******
 *******************/

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {10, 9, 8, 7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 5, 4}; //connect to the column pinouts of the keypad

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void enter_password()
{
  char key = kpd.getKey();
  if(key)
  {
      if (key == '#') // end of input
      {
        if (!check_password())
        {
          digitalWrite(myled, HIGH);
          take_picture();
          digitalWrite(myled, LOW);
          lcd.clear();
          lcd.print("Failed");
        }
        else
        {
          lcd.clear();
          lcd.print("Success");
        }
        delay(1000);
        setup_enter_password();
      }
      else if (key == '*')
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

/********************
 ******* Main *******
 *******************/

void setup() {
  // It will be turned off at the end of the sending.
  pinMode(myled, OUTPUT);
  
  Serial.begin(115200);
  /* If you just wanted to test
  test_send("Hello World!);
  delay(1000);
  digitalWrite(myled, LOW);
  return;
  */
  setup_cam();
  setup_lcd();

  // Setup button (FIXME, should use keypad)
  pinMode(butt, INPUT);
}

void loop() {
  enter_password();
  
  // read the state of the pushbutton value:
  /*int buttonState = digitalRead(butt);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    digitalWrite(myled, HIGH);
    delay(3000);
    take_picture();
    digitalWrite(myled, LOW);
  }*/
}

