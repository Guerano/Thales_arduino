// This is a snapshot sketch using the V0C706 library.
// On start, the Arduino will find the camera and then snap a
// photo, first printing the size then the content of the photo
// on the Serial port (Rx, Tx).

#include <Adafruit_VC0706.h>
#include <SoftwareSerial.h>         

// Using SoftwareSerial (Arduino 1.0+) or NewSoftSerial (Arduino 0023 & prior):
#if ARDUINO >= 100
// On Uno: camera TX connected to pin 2, camera RX to pin 3:
SoftwareSerial cameraconnection = SoftwareSerial(2, 3);
#else
NewSoftSerial cameraconnection = NewSoftSerial(2, 3);
#endif

Adafruit_VC0706 cam = Adafruit_VC0706(&cameraconnection);

// Simple function that send a string on Serial.
void test_send(String str)
{
  Serial.println(str.length());
  Serial.print(str);
}


const int myled = 11; // This led will be shining when sending on Serial
const int butt = 8; // Click on the button to send a picture

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

  // Setup button (FIXME, should use keypad)
  pinMode(butt, INPUT);
}

void take_picture()
{
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

int buttonState = 0;
void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(butt);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    digitalWrite(myled, HIGH);
    delay(3000);
    take_picture();
    digitalWrite(myled, LOW);
  }
}

