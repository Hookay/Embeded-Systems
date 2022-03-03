
#define B 26

float trig = 50;
float rest =19950;


void setup() {
  Serial.begin(9600);
  pinMode(B, OUTPUT);
  unsigned long timeBegin = micros();
  
  for (int i = 0; i < 500; i++)
  {
    digitalWrite(B, HIGH);
    delayMicroseconds(trig);
    digitalWrite(B, LOW);
    delayMicroseconds(rest);
  }
  
  unsigned long timeEnd = micros();
  unsigned long duration = timeEnd - timeBegin;
  double averageDuration = (double)duration / 1000.0;
  Serial.println(averageDuration,DEC);
}

void loop() {}
