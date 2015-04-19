/* 
read_scratch
drive
servo
 https://punchthrough.com/bean/the-arduino-reference/readscratchdata/
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


bool compareScratch( ScratchData * scratch1, ScratchData * scratch2 )
{
  bool matched = true;
  
  if ( scratch1->length != scratch2->length )
  {
    matched = false;
  }
  else
  {
    int length = min( scratch1->length, scratch2->length );
    int i = 0;
    
    while ( i < length )
    {
      if ( scratch1->data[i] != scratch2->data[i] )
      {
        matched = false;
        i = length;
      }
      i++;
    }
  }
  
    return matched;
}
 
 
void setup() 
{
  Serial.begin();
  servo.attach(2);
  Bean.enableWakeOnConnect( true ); 
    
}

ScratchData lastScratch;

void loop() 
{
   ScratchData thisScratch = Bean.readScratchData(1);
  
  bool matched = compareScratch( &thisScratch, &lastScratch );
   
  if ( matched == false )
  {
    lastScratch = thisScratch;
    //Serial.println(thisScratch);
    animate_servo();
    Bean.setLed(0,255,0);
    
    Bean.sleep(1000);
    
    Bean.setLed(0,0,0);
  } 
  
  Bean.sleep(1000);
}
