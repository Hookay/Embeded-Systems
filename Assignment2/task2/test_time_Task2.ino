// digital pin 2 has a pushbutton attached to it. Give it a name:
int pushButton = 27;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);

  //start measuring time in milisecond
  unsigned long timeBegin = micros();
   for (int i = 0; i < 500; i++)
  {
     //run task
     int button =digitalRead(pushButton);
     //Serial.println(button);
     
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

// the loop routine runs over and over again forever:
void loop() {
}
