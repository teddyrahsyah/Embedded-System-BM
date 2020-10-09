/****************************************************************************************
 *  Code is based on Blynk USB-Serial Example
 *  Make sure you go to C:\Users\Your Username\Documents\Arduino\libraries\Blynk\scripts
 *  Press CTRL + LMouse Button and select Open Command Windows Here
 *  Then type in command windws >> blynk-ser.bat -c COM2 and click enter
 *  Enjoy the Virtual IoT !!!
 ****************************************************************************************/
#include <BlynkSimpleStream.h>

// Pin Assignments
int redPin=8,greenPin=9,bluePin=10;

//Your app authentication token (can be fetched from your blynk app
char auth[] = "whXEzawmRiU9TNFG6IpsTu718SkkKTR-";



void setup()
{
  //Set the three LED pins as output
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);

  // Blynk will work through Serial
  Serial.begin(9600);
  Blynk.begin(auth, Serial);
}

void loop()
{
  // All the magic is here
  Blynk.run();
}
