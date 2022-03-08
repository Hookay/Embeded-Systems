//get pin
#define LED 32
#define POT 14
int error_code=0;

void setup() {
  //open serial port
  Serial.begin(9600);
  //assign pin to receive input
  pinMode(POT,INPUT);
  //assign pin to output
  pinMode(LED, OUTPUT);


  int s1 =0;
  for (int i = 0; i < 4; i++)
  {
    //run task
    s1 = s1 + digitalRead(POT);
        
  }
  s1=s1/4;

  if (s1 > 0.5){
      error_code = 1;
  }else{
      error_code = 0;  
  } 

  //start measuring time in milisecond
  unsigned long timeBegin = micros();
   for (int i = 0; i < 500; i++)
  {

    
    //if switch is used
    if(error_code==1){
       
      //create 50 microseconds high to light up lamp with switch
      digitalWrite(LED, HIGH);
    }else{
      digitalWrite(LED, LOW);
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
