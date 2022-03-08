#define squareWave 34

void setup() {
  Serial.begin(9600);
  pinMode(SQW, INPUT);
}

void loop(){

//start counting
unsigned long timeBegin = micros();
//run it for 500 times
for (int i = 0; i < 500; i++)
{

float s1;
float s2;

s1 = pulseIn(SQW,HIGH);
s2 = pulseIn(SQW,LOW);
float period = s1+s2; //is in microseconds
float freq=1e6/period; //dividing by 1e6 as this is 1micro in second as you need to scale it


//Serial.println(freq);

  //stop counting
  unsigned long timeEnd = micros();
  //getduration
  unsigned long duration = timeEnd - timeBegin;
  //get average
  double averageDuration = (double)duration / 500.0;
  //show it in port
  Serial.println(averageDuration,DEC);
  
}
