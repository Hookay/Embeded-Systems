//get pin
#define B 26
#define pushButton 27
#define SQW 34
#define PO 33
#define LED 14

//error for task 7
int error_code=0;
//add trigger signal variables for task1
float trig = 50;
float rest =19950;


void setup() {
  //open serial port
  Serial.begin(9600);
  //assign pin to output for oscilloscope
  pinMode(B, OUTPUT);
  // make the pushbutton's pin an input
  pinMode(pushButton, INPUT)
   //assign pin to receive input from potentiometer
  pinMode(PO,INPUT);
  //assign pin to receive input from signal generator
  pinMode(SQW, INPUT);
  //assign pin to  output for LED
  pinMode(LED, OUTPUT);



int counter = 0;

int button=0;
float freq = 0;
int pot=0;

void loop() {
counter++;
task1();
if(counter 10%==0){
  task2();
}
if(counter 50%==0){
  task3();
}
if(counter %2==0){
  task4();
  task5();
}
if(counter 5%==0){
  task6();
}
if(counter 17%==0){
  task7();
  task8();
}
if(counter 250%==0){
  task9(button,freq,pot); 
}



//task 1 Read oscilloscope
task1(){
  digitalWrite(B, HIGH);
  delayMicroseconds(trig);
  digitalWrite(B, LOW);
  delayMicroseconds(rest);
}

//task 2 read switch button
int task2(){
  button =digitalRead(pushButton);
  return button;
}

//task3 read square wave
float task3(){
  float s1;
  float s2;

  s1 = pulseIn(SQW,HIGH);
  s2 = pulseIn(SQW,LOW);
  float period = s1+s2; //is in microseconds
  freq=1e6/period; //dividing by 1e6 as this is 1micro in second as you need to scale it
  return freq
 
}

//Task 4 read in potentiometer value
task4(){
  int potentiometer =digitalRead(PO);
  
}

//Task5  filter
int task5(){
  for (int i = 0; i < 4; i++){
    //run task
    pot = pot+digitalRead(PO);}
  pot=pot/4;
  return pot
}

//Task6 loop 1000 times 
task6(){
  for (int i = 0; i < 1000; i++)
  { 
    __asm__ __volatile__ ("nop");}
}


//Task7 get error from potentiometer
task7(){
  if (pot > 0.5){
    error_code = 1;
  }else{
    error_code = 0;}
}

//Task8 display error on LED
task8(){
  //if switch is used
  if(error_code==1){     
    //create 50 microseconds high to light up lamp with switch
    digitalWrite(LED, HIGH);
  }else{
    digitalWrite(LED, LOW);}
}

//Task9 print button, frequency and filter value
task9(button, freq, pot){
  Serial.print(button);
  Serial.print(", ");
  Serial.print(freq); 
  Serial.print("Hz, ");
  Serial.println(pot);
}
}
