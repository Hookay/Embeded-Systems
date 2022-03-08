//get pin

#define PO 33


void setup() {
  //open serial port
  Serial.begin(9600);
  //assign pin to receive input
  pinMode(PO,INPUT);

  int pot=0;
  for (int i = 0; i < 4; i++)
  {
     //run task
    pot = pot+digitalRead(PO);

  }
  //start measuring time in milisecond
  unsigned long timeBegin = micros();
   for (int i = 0; i < 500; i++)
  {
     int filter=pot/4;
     //Serial.println(filter);
     
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
