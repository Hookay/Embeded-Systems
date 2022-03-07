//get pin
#define B 26
#define SIG 33
#define AN 14
#define SW1 25

int error_code=0;

void setup() {
  //open serial port
  Serial.begin(9600);
  //assign pin to receive input
  pinMode(AN,INPUT);
   //assign pin to receive input
  pinMode(SIG,INPUT);
  //assign pin to output
  pinMode(B, OUTPUT);
   //assign pin to receive input
  pinMode(SW1,INPUT);

      //run task
      int s3 =digitalRead(SIG);
     
      int s2 =digitalRead(SW1);
      int s1 =0;
      for (int i = 0; i < 4; i++)
    {
        //run task
        s1 = s1 + digitalRead(AN);
        // Serial.println(s1,DEC);
    }
    s1=s1/4;

    if (s1 > 0.5){
      error_code = 1;
    }else{
      error_code = 0;
    // Serial.println(s1,DEC);
    } 
     //if switch is used
    if(error_code==1){
          
      //create 50 microseconds high to light up lamp with switch
      digitalWrite(B, HIGH);
    }else{
      digitalWrite(B, LOW);
    }
  //start measuring time in milisecond
  unsigned long timeBegin = micros();
   for (int i = 0; i < 500; i++)
  {  
      Serial.print(s2);
      Serial.print(", ");
      Serial.print(s3); 
      Serial.print("Hz, ");
      Serial.println(s1); 
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
