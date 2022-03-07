//get pin
#define B 26
#define SW1 14
//add trigger signal variables
float trig = 50;

void setup() {
  //open serial port
  Serial.begin(9600);
  //assign pin to receive input
  pinMode(SW1,INPUT);
   //assign pin to output
  pinMode(B, OUTPUT);
  //start measuring time in milisecond
  unsigned long timeBegin = micros();
   for (int i = 0; i < 500; i++)
  {
     //run task
     int s1 =digitalRead(SW1);
     //if switch is used
     if(s1==1){
          //run code
          //create 50 microseconds high to light up lamp with switch
          digitalWrite(B, HIGH);
          delayMicroseconds(trig);


      }else{
          digitalWrite(B, LOW);
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
