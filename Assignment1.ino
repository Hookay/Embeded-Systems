/*
The task is to create a signal which can be interupted with a switch or changed with another switch. 

Author:Reka Hegedus
 */
 

//pins
#define A 25
#define B 26
#define SW1 14
#define SW2 27

//variables 
int a = 800;
int b = 500;
int c =0;
int c1 = 11;
int d = 2500;

 
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize pins inputs and outputs. A and B is LED SW1, SW2 is switches
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(SW1,INPUT);
  pinMode(SW2,INPUT);
  
 
}


  // the loop function runs over and over again forever checking for changes
  void loop() {
  
    //check if there is input from the switches
    int s1 =digitalRead(SW1);
    int s2 =digitalRead(SW2);
    
    //if the first switch is pressed do this
    if(s1==0){
    
      // check if the second switch is pressed 
      if(s2==1){
         //if yes change to different sequence
         c=c1-3; }
      else{
        // if not carry on sequence
        c=c1;
      }
      
      //signal B starts every sequence
      digitalWrite(B,HIGH);
      delay(50);
      digitalWrite(B,LOW);
      
      //code runs repetedly c times signal A
      for(int i=1;i<=c;i++){
        digitalWrite(A, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay((a + (50*i)));     // wait for a given time (increases with rounds)
        digitalWrite(A, LOW);    // turn the LED off by making the voltage LOW
        delay(b);                // wait for a time
       
      }
      //the delay after the sequence
      digitalWrite(A,LOW);
      delay(d);



    }else{
     digitalWrite(A, LOW);   // turn the LED off                   
     digitalWrite(B, LOW);    // turn the LED off by making the voltage LOW
    }
  }
