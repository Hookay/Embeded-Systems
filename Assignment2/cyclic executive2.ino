//get pin
#define B 26
#define pushButton 27
#define SQW 34
#define PO 33
#define LED 14

//create global variables so method can use them easily
//error for task 7
int error_code=0;
//trigger signal variable for task1
float trig = 50;
//counter to track time
int counter; 
//variable for switch
int button=0;
//variable for the frequency
float freq = 0;
//variable for potentiometer
float pot=0;
//variable for the filtering value
float filter=0;

void setup() {
  //open serial port in order to be able to display values in task9
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
    //make LED output light up
    digitalWrite(B, HIGH);
    //for 50 microseconds
    delayMicroseconds(trig);
    //then go low the period which we will call it will decide how long (20000microseconds)
    digitalWrite(B, LOW);
    
  }

  //task 2 read switch button
  void task2(){
    //read in value check if the button been pushed
    button =digitalRead(pushButton);
    
  }

  //task3 read square wave
  void task3(){
    
    //get samples from high level and low level
    float s1 = pulseIn(SQW,HIGH);
    float s2 = pulseIn(SQW,LOW);
    //create the whole period by adding it 
    float period = s1+s2; 
    //scale the value to seconds in order to get the frequency
    freq=1e6/period; 
    
  
  }

  //Task 4 read in potentiometer value
  void task4()
  {//read in the value of the potentiometer (0 or 1)
    pot =digitalRead(PO);  
    
  }

  //Task5  filter
  void task5()
  //take the last four reading of the potentiometer  
  { float sum=0;
    for (int i = 0; i < 4; i++){
      //run task
      sum = sum+pot;
    }
    //and filter it to get a more stable reading of the change since they both run on the same frequency
    filter=sum/4;
  }

  //Task6 loop 1000 times 
  void task6(){
    //repeat this loop for a 10000 times
    for (int i = 0; i < 1000; i++)
    { 
      __asm__ __volatile__ ("nop");
    }
  }

  //Task7 get error from potentiometer
  void task7(){
    //if the filtered value is larger than half of the maximums(1) input then then we have a one othervise 0 to indicate change in reading
    if (filter > 0.5){
      error_code = 1;
    }else{
      error_code = 0;}
    
  }

  //Task8 display error on LED
  void task8(){
    
    //if switch is used
    if(error_code==1){
         
      //create 50 microseconds high to light up lamp with switch and show error_code is 1
      digitalWrite(LED, HIGH);
    }else{
      //esle keep it switched off 
      digitalWrite(LED, LOW);}
  }

  //Task9 print button, frequency and filter value
  void task9(){
    //print button value
    Serial.print(button);
    //print a coma in the same line
    Serial.print(", ");
    //print frequency value
    Serial.print(freq); 
    //print Hz
    Serial.print("Hz, ");
    //print the potentiometer value
    Serial.println(filter);
  }



void loop() {
 //I use a conversion from microseconds to loop count I noticed that a loop to run it takes 1.5 times more than 
 //if I run it with microseconds method count. The advantage of counting the loop is that I can actually loop the 
 //tasks not just runa counter and set it back to 0 so counter does not have to store just the neccesary values.  
  
// make sure the value of the counter does not store larger number then needed  
if(counter>7500000){
    // if its more then the number of microseconds we need to complete all the tasks set it back to 0
    counter=0;
}
// start counting  
counter++;
 
  //run at 50Hz= 20000 microseconds = 30000 in loop time 5% applied
  if(counter %30000==0){
    
    task1();
    
  }
  //run at 24Hz= 40000 microseconds =60000 in loop time 5% applied
  if(counter %60000==0){
    task4();
    task5(); 
  }
  //run at 10Hz= 100000 microseconds =150000 in loop time 
  if(counter %150000==0){
    task6();
  }
  //run at 5Hz= 200000 microseconds =300000 in loop time 
  if(counter %300000==0){
    task2();
  }
  //run at 3Hz= 320000 microseconds =480000 in loop time  5% applied
  if(counter %(480000)==0){
    
    task7();
    task8();
  }
  //run at 1Hz= 1000000 microseconds =1500000 in loop time 
  if(counter %1500000==0){
    task3();
  }
  //run at 0.2Hz= 5000000 microseconds =7500000 in loop time 
  if(counter %7500000==0){
    task9(); 
  }

  
}
