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
float a = 800;
float b = 500;
float pulse =0.0;
float c = 11.0;
float d = 2500;
float trig= 50;

 
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize pins inputs and outputs. A and B is LED SW1, SW2 is switches
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(SW1,INPUT);
  pinMode(SW2,INPUT);
  
  //Serial.begin(9600); // open the serial port at 9600 bps:
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
         pulse=c-3; }
      else{
        // if not carry on sequence
        pulse=c;
      }
      
      //signal B starts every sequence
      digitalWrite(B,HIGH);
      
      delayMicroseconds(trig);
      digitalWrite(B,LOW);
      
      //code runs repetedly c times signal A
      for(float i=0.0;i<pulse;i++){
        
        // create variable for delay add to  a  50 micro s and at each run increase the added value by mulitiplying it wit index 1 50*0,2 50*1...
        float dd = (a + (50*i));
     
        digitalWrite(A, HIGH);   // turn the LED on (HIGH is the voltage level)
        delayMicroseconds(dd);   // wait for a given time (increases with rounds)
        digitalWrite(A, LOW);    // turn the LED off by making the voltage LOW
        delayMicroseconds(b);    // wait for a time                
       
      }
      //the delay after the sequence
      digitalWrite(A,LOW);
      delayMicroseconds(d);


    }else{
     digitalWrite(A, LOW);   // turn the LED off                   
     digitalWrite(B, LOW);    // turn the LED off by making the voltage LOW
    }
  }
