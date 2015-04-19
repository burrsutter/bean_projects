/*
Driving Servo via Light Blue Bean
https://github.com/gpxlBen/BeanBot/blob/master/BeanBot%20Sketch/beanBot/beanBot.ino

*/
#include <Servo.h>

Servo servo;
int pos = 0;
int maxpos = 160;

void animate_servo() {
 for(pos = 0; pos < maxpos; pos += 1)  
  {                                  
    servo.write(pos);              
    delay(15);                       
  } 
  for(pos = maxpos; pos>=1; pos-=1)     
  {                                
    servo.write(pos);              
    delay(15);     
  } 
}

void setup() {
  Serial.begin();
  servo.attach(2);
}

void loop() {
  animate_servo();
  Bean.sleep(2000);
}

