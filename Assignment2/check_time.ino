int t;

void setup(){
  Serial.begin(9600);
}
void loop(){
  
  t = micros();
  


  if(t % 20000==0){
    Serial.print("Time: ");
    Serial.println(t);
    delay(1000);
    
  }



}
