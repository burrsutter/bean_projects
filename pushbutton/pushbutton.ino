/*
http://www.hackster.io/3043/lightblue-bean-octoblu
https://www.dropbox.com/s/q5wid13jz0uw8tv/2015-03-25%2019.35.33.jpg?dl=0
the solder in 5 was a goof that I did not clean up well.
https://www.dropbox.com/s/cq7eshvbf3f3nni/2015-03-25%2019.35.41.jpg?dl=0
*/

uint16_t numClicks = 0;

const int buttonPin = 4; 
const bool DEBUG = true;
bool connected = false;

void setup() {
  Serial.begin(); 
  pinMode(4,INPUT);
  Bean.setLed(0, 0, 0);
  
  // I only care to capture the click events IF something is connected to me
  Bean.enableWakeOnConnect( true ); 
}

void loop() {
  uint8_t buffer[2];
  uint16_t button = digitalRead(4);   

  // write state of button to scratch 1
  buffer[0] = button & 0xFF;
  buffer[1] = button >> 8;
  
  Bean.setScratchData(1, buffer, 2);
 
 if (button == 1) {
   if (DEBUG) {
     Serial.println("button clicked");
   }
   
   numClicks++;
   
   // the next lines blink the onboard LED green
   Bean.setLed(0, 255, 0);
   connected = Bean.getConnectionState();
   
   uint16_t batteryReading =  Bean.getBatteryVoltage(); 
   
   Bean.sleep(50);
   Bean.setLed(0, 0, 0);
   
   if (DEBUG) {
     Serial.println(numClicks);
     // This is not currently displaying correctly
     // String stringToPrint = String();
     // stringToPrint = "Battery: " + (batteryReading / 100);
     // stringToPrint = stringToPrint + "." + (batteryReading % 100) + " V";
     // Serial.println(stringToPrint);
     if (connected)
       Serial.println("Connected");
   } 
 }
 Bean.sleep(100);
}


