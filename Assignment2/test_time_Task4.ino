//get pin

#define PO 33


void setup() {
  //open serial port
  Serial.begin(9600);
  //assign pin to receive input
  pinMode(PO,INPUT);

  //start measuring time in milisecond
  unsigned long timeBegin = micros();
   for (int i = 0; i < 500; i++)
  {
     //run task
     int s1 =digitalRead(PO);
     //Serial.println(s1);
     
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
