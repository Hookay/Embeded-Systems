//get pin

//#define SIG 14


void setup() {
  //open serial port
  Serial.begin(9600);
  //assign pin to receive input
 // pinMode(SIG,INPUT);

  //start measuring time in milisecond
  unsigned long timeBegin = micros();

   for (int i = 0; i < 500; i++)
  {
      for (int i = 0; i < 1000; i++)
    { 
        __asm__ __volatile__ ("nop");
      
    }
    // Serial.println(s1,DEC);
     
  }
  //end count
  unsigned long timeEnd = micros();
  //calculate elapsed time
  unsigned long duration = timeEnd - timeBegin;
  //get the average of the tasks
  double averageDuration = (double)duration / 500.0;
  //print the result in the serial port
  Serial.println(averageDuration,DEC);
}

void loop() {


}
