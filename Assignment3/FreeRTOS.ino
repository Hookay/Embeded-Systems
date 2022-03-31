#define B 26
#define LED 14
#define pushButton 27
#define SQW 34
#define PO 33

//create global variables so method can use them easily
static SemaphoreHandle_t mutex;       // lock-release Serial resource
//variable for switch
int button=0;
//variable for the frequency
float freq = 0;
//variable for potentiometer
float pot=0;
//variable for the filtering value
float filter=0;
//error for task 7
int error_code=0;
//variable for the que handler
static QueueHandle_t queue_1;

//WATCHDOG SIGNAL
void task1(void * parameters){
  //trigger signal variable for task1 watchdog signal
  float trig = 50;
  for(;;){ // infinite loop FreeRTOS will pause it with vTaskDelay
    //start measuring task execution time
     long int t1 = millis();
    //make LED output light up
    digitalWrite(B, HIGH);
    //for 50 microseconds
    delayMicroseconds(trig);
    // Turn the LED off
    digitalWrite(B, LOW);
     //get instant time
     long int t2 = millis();
     // measure the task so its execution time known so the delay can be calculated to complete the correct frequency it repeats
     long int time= t2-t1;
    // Pause the task again for 20ms -task execution time so other tasks can be executed then repeat 50Hz= 20 miliseconds
    vTaskDelay( (20-time)/ portTICK_PERIOD_MS);
  }
}

//READ BUTTON PRESS
void task2(void * parameters){
  for(;;){ // infinite loop FreeRTOS will pause it with vTaskDelay
    //start measuring task execution time
    long int t1 = millis();
    //read in value check if the button been pushed update its value
    button =digitalRead(pushButton);
    //get instant time
     long int t2 = millis();
    // measure the task so its execution time known so the delay can be calculated to complete the correct frequency it repeats
     long int time= t2-t1;
    // Pause the task again for 200ms -task execution time so other tasks can be executed then repeat 5Hz= 200 miliseconds
    vTaskDelay((200-time) / portTICK_PERIOD_MS);
  }
}

//READ SQUARE WAVE SIGNAL
void task3(void * parameters){
  for(;;){ // infinite loop FreeRTOS will pause it with vTaskDelay
    //start measuring task execution time
    long int t1 = millis();
    //create value to store sample
    float s;
    //get samples from high level 
    s = pulseIn(SQW,HIGH);
    //50% duty cycle create the whole period by dubleing it
    float period = 2*s; 
    //scale the value to seconds in order to get update frequency value
    freq=1e6/period; 
    //get instant time
    long int t2 = millis();
    // measure the task so its execution time known so the delay can be calculated to complete the correct frequency it repeats
    long int time= t2-t1;
    // Pause the task again for 1000ms -task execution time so other tasks can be executed then repeat 1Hz= 1000 miliseconds
    vTaskDelay((1000-time) / portTICK_PERIOD_MS);
  }
}

//READ POTENTIOMETER
void task4(void * parameters){
  
  for(;;){ // infinite loop FreeRTOS will pause it with vTaskDelay
    //start measuring task execution time
    long int t1 = millis();
    //read in analogue value
    pot = analogRead(PO);
    // Read from queue (wait max time if queue is empty)
    xQueueSend(queue_1, &pot, portMAX_DELAY);
    //get instant time
    long int t2 = millis();
    // measure the task so its execution time known so the delay can be calculated to complete the correct frequency it repeats
    long int time= t2-t1;
    // Pause the task again for 40ms -task execution time so other tasks can be executed then repeat 24Hz= 40 miliseconds
    vTaskDelay((40-time) / portTICK_PERIOD_MS);
  }
}
// CREATE FILTER VALUES
void task5(void * parameters){

  for(;;){ // infinite loop FreeRTOS will pause it with vTaskDelay
    //start measuring task execution time
    long int t1 = millis();
     //initialise received filter variable and average variable
     float filt=0;
     float av =0;
    //receive the values from the queue filt is going to be the received values
    if(xQueueReceive(queue_1, &filt, portMAX_DELAY) == pdPASS){
      //take the last four reading of the potentiometer as filt always changing with que reeding 
      for(int f=0;f<4;f++){
     
      av=av+filt;
      }
      //average it and update filter value
      filter = (av/4);
      //reset average for the new loop to receive the fresh readings
      av=0;    
      
    }
    //get instant time
    long int t2 = millis();
    // measure the task so its execution time known so the delay can be calculated to complete the correct frequency it repeats
    long int time= t2-t1;
    // Pause the task again for 40ms -task execution time so other tasks can be executed then repeat 24Hz= 40 miliseconds
    vTaskDelay((40-time) / portTICK_PERIOD_MS);

  }
}
//LOOP 1000
void task6(void * parameters){
  for(;;){ // infinite loop FreeRTOS will pause it with vTaskDelay
     //start measuring task execution time
     long int t1 = millis();
    //repeat this loop for 10000 times
    for (int i = 0; i < 1000; i++)
    { 
      __asm__ __volatile__ ("nop");
    }
    //get instant time
    long int t2 = millis();
    // measure the task so its execution time known so the delay can be calculated to complete the correct frequency it repeats
    long int time= t2-t1;
    // Pause the task again for 100ms -task execution time so other tasks can be executed then repeat 10Hz= 100 miliseconds
    vTaskDelay((100-time) / portTICK_PERIOD_MS);
  }
}

//PRODUCE ERROR CODE
void task7(void * parameters){
  
  for(;;){ // infinite loop FreeRTOS will pause it with vTaskDelay
  

    //start measuring task execution time
    long int t1 = millis();
      // if fitered value is bigger then the half of the total reading value from the potentiometer error cde 1 else 0
      if (filter > (4095/2)){
        error_code = 1;
        
      }else{
        error_code = 0;   
        }
    //get instant time
    long int t2 = millis();
    // measure the task so its execution time known so the delay can be calculated to complete the correct frequency it repeats
    long int time= t2-t1;
    // Pause the task again for 320ms -task execution time so other tasks can be executed then repeat 3Hz= 320 miliseconds
    vTaskDelay((320-time) / portTICK_PERIOD_MS);
  }
}
//VISUALISE ERROR CODE
void task8(void * parameters){
  for(;;){ // infinite loop FreeRTOS will pause it with vTaskDelay
    //start measuring task execution time
    long int t1 = millis();
    //potentiometer used
    if(error_code==1){
         
      //light up lamp  if error_code is 1
      digitalWrite(LED, HIGH);
    }else{
      //esle keep it switched off 
      digitalWrite(LED, LOW);}
    //get instant time
    long int t2 = millis();
    // measure the task so its execution time known so the delay can be calculated to complete the correct frequency it repeats
    long int time= t2-t1;
    
    // Pause the task again for 320ms -task execution time so other tasks can be executed then repeat 3Hz= 320 miliseconds
    vTaskDelay((320-time) / portTICK_PERIOD_MS);
  }
}
//PRINT EVERY 5 SECONDS BUT ONLY WHEN THE BUTTON IS PUSHED
void task9(void * parameters){
  for(;;){ // infinite loop FreeRTOS will pause it with vTaskDelay
  
    //start measuring task execution time
    long int t1 = millis();
    //if button pushed execute this
    if(button==1){
      // Lock Serial resource with a mutex
      xSemaphoreTake(mutex, portMAX_DELAY);
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
      // Release Serial resource with a mutex
      xSemaphoreGive(mutex);
    
    
    }
    //get instant time
    long int t2 = millis();
    // measure the task so its execution time known so the delay can be calculated to complete the correct frequency it repeats
    long int time= t2-t1;
    // Pause the task again for 5000ms -task execution time so other tasks can be executed then repeat 0.2Hz= 5000 miliseconds
    vTaskDelay((5000-time) / portTICK_PERIOD_MS);
    
  }
}

void setup() {
  //open serial port in order to be able to display values in task9
  Serial.begin(9600);
  //assign pin to output for oscilloscope
  pinMode(B, OUTPUT);
  // make the pushbutton's pin an input
  pinMode(pushButton, INPUT);
  //assign pin to receive input from signal generator
  pinMode(SQW, INPUT);
  //assign pin to receive input from potentiometer
  pinMode(PO,INPUT);
  //assign pin to  output for LED
  pinMode(LED, OUTPUT);
  //create queue size 4 to receive and send values inbetween task 4 and 5
  queue_1 = xQueueCreate(4, sizeof(int));
  //make sure if there is no values in queue we get a warning
  if (queue_1 == NULL) {
  Serial.println("Something went wrong");
  }
  //mutex locks the thread  to make sure only that can enter the critical section
  mutex = xSemaphoreCreateMutex();

  xTaskCreate( 
    task1,    // function called
    "watchDog",   // name the task for clarity
    1000,            // stack size in bites
    NULL,            // no parameter to pass
    1,               // priority of this task
    NULL);           // Handler if not NULL   returns pdPASS at succesful task creation otherwise an error
  xTaskCreate( 
    task2,    // function called
    "pushButton",   // name the task for clarity
    1000,            // stack size in bites
    NULL,            // no parameter to pass
    1,               // priority of this task
    NULL);           // Handler if not NULL   returns pdPASS at succesful task creation otherwise an error

  xTaskCreate( 
    task3,    // function called
    "Square",   // name the task for clarity
    1000,            // stack size in bites
    NULL,            // no parameter to pass
    1,               // priority of this task
    NULL);           // Handler if not NULL   returns pdPASS at succesful task creation otherwise an error

 
  xTaskCreate( 
    task4,    // function called
    "potentiometer",   // name the task for clarity
    1000,            // stack size in bites
    NULL,            // no parameter to pass
    1,               // priority of this task
    NULL);           // Handler if not NULL   returns pdPASS at succesful task creation otherwise an error

    xTaskCreate( 
    task5,    // function called
    "filter",   // name the task for clarity
    1000,            // stack size in bites
    NULL,            // no parameter to pass
    1,               // priority of this task
    NULL);           // Handler if not NULL   returns pdPASS at succesful task creation otherwise an error

    xTaskCreate( 
    task6,    // function called
    "loop",   // name the task for clarity
    1000,            // stack size in bites
    NULL,            // no parameter to pass
    1,               // priority of this task
    NULL);          // Handler if not NULL   returns pdPASS at succesful task creation otherwise an error


    xTaskCreate( 
    task7,    // function called
    "error",   // name the task for clarity
    1000,            // stack size in bites
    NULL,            // no parameter to pass
    1,               // priority of this task
    NULL);           // Handler if not NULL   returns pdPASS at succesful task creation otherwise an error

    xTaskCreate( 
    task8,    // function called
    "lightError",   // name the task for clarity
    1000,            // stack size in bites
    NULL,            // no parameter to pass
    1,               // priority of this task
    NULL);           // Handler if not NULL   returns pdPASS at succesful task creation otherwise an error

    xTaskCreate( 
    task9,    // function called
    "Print",   // name the task for clarity
    1000,            // Stack size (bytes)
    NULL,            // no parameter to pass
    1,               // priority of this task
    NULL);           // Handler if not NULL   returns pdPASS at succesful task creation otherwise an error

}

void loop() {

}
