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
int counter = micros();
int button=0;
float freq = 0;
int pot=0;

void setup() {
  //open serial port
  Serial.begin(9600);
  //assign pin to output for oscilloscope
  pinMode(B, OUTPUT);
  // make the pushbutton's pin an input
  pinMode(pushButton, INPUT);
   //assign pin to receive input from potentiometer
  pinMode(PO,INPUT);
  //assign pin to receive input from signal generator
  pinMode(SQW, INPUT);
  //assign pin to  output for LED
  pinMode(LED, OUTPUT);
}

  //task 1 Read oscilloscope
  void task1(){
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
    return freq;
  
  }

  //Task 4 read in potentiometer value
  void task4()
  {
    int potentiometer =digitalRead(PO);  
  }

  //Task5  filter
  int task5()
  {
    for (int i = 0; i < 4; i++){
      //run task
      pot = pot+digitalRead(PO);
    }
    pot=pot/4;
    return pot;
  }

  //Task6 loop 1000 times 
  void task6(){
    for (int i = 0; i < 1000; i++)
    { 
      __asm__ __volatile__ ("nop");
    }
  }


  //Task7 get error from potentiometer
  void task7(){
    if (pot > 0.5){
      error_code = 1;
    }else{
      error_code = 0;}
  }

  //Task8 display error on LED
  void task8(){
    //if switch is used
    if(error_code==1){     
      //create 50 microseconds high to light up lamp with switch
      digitalWrite(LED, HIGH);
    }else{
      digitalWrite(LED, LOW);}
  }

  //Task9 print button, frequency and filter value
  void task9(){
    Serial.print(button);
    Serial.print(", ");
    Serial.print(freq); 
    Serial.print("Hz, ");
    Serial.println(pot);
  }

void loop() {

  if(counter %20000==0){
    task1();
  }
  if(counter %200000==0){
    task2();
  }
  if(counter %1000000==0){
    task3();
  }
  if(counter %40000==0){
    task4();
    task5();
  }
  if(counter %100000==0){
    task6();
  }
  if(counter %((1/3)*1000000)==0){
    task7();
    task8();
  }
  if(counter %5000000==0){
    task9(); 
  }
}
