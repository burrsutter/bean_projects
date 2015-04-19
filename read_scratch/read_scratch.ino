/*
 reading scratch data
 responding to scratch data
 https://punchthrough.com/bean/the-arduino-reference/readscratchdata/
 
*/

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
    
    Bean.setLed(0,255,0);
    
    Bean.sleep(1000);
    
    Bean.setLed(0,0,0);
  } 
  
  Bean.sleep(1000);
}
