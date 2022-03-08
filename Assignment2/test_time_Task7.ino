//get pin

#define POT 14
int error_code=0;

void setup() {
  //open serial port
  Serial.begin(9600);
  //assign pin to receive input
  pinMode(POT,INPUT);

  int s1 =0;

  for (int i = 0; i < 4; i++)
  {
    //run task
    s1 = s1 + digitalRead(POT);
    // Serial.println(s1,DEC);
  }
  s1=s1/4;

    //start measuring time in milisecond
   unsigned long timeBegin = micros();
   for (int i = 0; i < 500; i++)
  {     
    if (s1 > 0.5){
      error_code = 1;
    }else{
      error_code = 0;
      
    } 
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
