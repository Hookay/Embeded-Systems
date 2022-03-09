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
int counter; 
int button=0;
float freq = 0;
float pot=0;
float filter=0;
int t;

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
    
  }

  //task 2 read switch button
  void task2(){
    button =digitalRead(pushButton);
    
  }

  //task3 read square wave
  void task3(){
    float s1;
    float s2;

    s1 = pulseIn(SQW,HIGH);
    s2 = pulseIn(SQW,LOW);
    float period = s1+s2; //is in microseconds
    freq=1e6/period; //scale it
    
  
  }

  //Task 4 read in potentiometer value
  void task4()
  {
    pot =digitalRead(PO);  
    
  }

  //Task5  filter
  void task5()
  { float sum=0;
    for (int i = 0; i < 4; i++){
      //run task
      sum = sum+pot;
    }
    filter=sum/4;
  }

  //Task6 loop 1000 times 
  void task6(){
    //Serial.println(counter);
    for (int i = 0; i < 1000; i++)
    { 
      __asm__ __volatile__ ("nop");
    }
  }

  //Task7 get error from potentiometer
  void task7(){
    if (filter > 0.5){
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
if(counter>7500000){
    counter=0;
}
  
counter++;
 

  if(counter %30000==0){
    
    task1();
    
  }
  if(counter %60000==0){
    task4();
    task5(); 
  }
  if(counter %150000==0){
    task6();
  }
  if(counter %300000==0){
    task2();
  }
  if(counter %(510000)==0){
    
    task7();
    task8();
  }
  if(counter %1500000==0){
    task3();
  }
  if(counter %7500000==0){
    task9(); 
  }

  
}
