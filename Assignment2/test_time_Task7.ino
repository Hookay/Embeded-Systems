//get pin

#define SIG 14
int error_code=0;

void setup() {
  //open serial port
  Serial.begin(9600);
  //assign pin to receive input
  pinMode(SIG,INPUT);

  //start measuring time in milisecond
  unsigned long timeBegin = micros();
       int s1 =0;
      for (int i = 0; i < 4; i++)
    {
        //run task
        s1 = s1 + digitalRead(SIG);
        // Serial.println(s1,DEC);
    }
    s1=s1/4;
   for (int i = 0; i < 500; i++)
  {
       

    if (s1 > 0.5){
      error_code = 1;
    }else{
      error_code = 0;
    // Serial.println(s1,DEC);
    } 
  }
  //end count
  unsigned long timeEnd = micros();
  //calculate elapsed time
  unsigned long duration = timeEnd - timeBegin;
  //get the average of the tasks
  double averageDuration = (double)duration / 1000.0;
  //print the result in the serial port
  Serial.println(averageDuration,DEC);
}

void loop() {


}
