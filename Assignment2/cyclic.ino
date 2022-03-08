//get pin
#define B 26
int pushButton = 27;
#define PO 33
#define POT 14
int error_code=0;
//add trigger signal variables
float trig = 50;
float rest =19950;


void setup() {
  //open serial port
  Serial.begin(9600);
  //assign pin to output
  pinMode(B, OUTPUT);
  // make the pushbutton's pin an input:
  pinMode(pushButton, INPUT);
   //assign pin to receive input
  pinMode(PO,INPUT);
  //assign pin to receive input
  pinMode(POT,INPUT);
    


}

void loop() {
//task 1
digitalWrite(B, HIGH);
delayMicroseconds(trig);
//create 19950 low state
digitalWrite(B, LOW);
delayMicroseconds(rest);


//task 2 
//read switch button
int button =digitalRead(pushButton);

//task3


//Task 4
int s1 =digitalRead(PO);

//Task5 
int pot=0;
for (int i = 0; i < 4; i++)
{
//run task
  pot = pot+digitalRead(PO);
}

//Task6
for (int i = 0; i < 1000; i++)
{ 
  __asm__ __volatile__ ("nop");
      
}

//Task7
if (pot > 0.5){
      error_code = 1;
}else{
      error_code = 0;
      
}

//Task8
//if switch is used
if(error_code==1){     
  //create 50 microseconds high to light up lamp with switch
  digitalWrite(LED, HIGH);
}else{
  digitalWrite(LED, LOW);
}

//Task9
Serial.print(button);
Serial.print(", ");
Serial.print(s3); 
Serial.print("Hz, ");
Serial.println(pot);
     
  







}
