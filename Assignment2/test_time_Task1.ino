
//get pin
#define B 26
//add trigger signal variables
float trig = 50;
float rest =19950;


void setup() {
  //open serial port
  Serial.begin(9600);
  //assign pin to output
  pinMode(B, OUTPUT);
  //start counting
  unsigned long timeBegin = micros();
  //run it for 500 times
  for (int i = 0; i < 500; i++)
  {
    //run code
    //create 50 microseconds high
    digitalWrite(B, HIGH);
    delayMicroseconds(trig);
    //create 19950 low state
    digitalWrite(B, LOW);
    delayMicroseconds(rest);
  }
  //stop counting
  unsigned long timeEnd = micros();
  //getduration
  unsigned long duration = timeEnd - timeBegin;
  //get average
  double averageDuration = (double)duration / 1000.0;
  //show it in port
  Serial.println(averageDuration,DEC);
}

void loop() {}
