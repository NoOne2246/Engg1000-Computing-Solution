//declare variables
int interruptPin = 2; 
int interruptNo = 0;
long interruptTime[100];
int interruptState[100];
long interruptLength[100];
int dataLength = 0;
int ledPin = 13;
char temp;
void interruptPinChange();

// -------------------------------------------------------
// The setup() method runs once, when the sketch starts
// -------------------------------------------------------
void setup(){  
  
  // Set up the interupt
  pinMode(interruptPin, INPUT);
  pinMode(ledPin, OUTPUT);
  attachInterrupt(interruptNo, interruptPinChange, CHANGE);

  // initialize the serial communications
  Serial.begin(9600); 
  Serial.println("Initialised");
  
}

// -------------------------------------------------------
// The loop() method runs over and over again
// -------------------------------------------------------
void loop(){
  
  // Use the USB Serial Comms as a substitute for a genuine 
  // signal coming into InterruptPin0
  // Connect Digital IO Pins 0 & 2
  
  // Has there been a transmission
  if (Serial.available() > 0) {
    
    // Wait for all the data to arrive
    delay(100);
    
    
    //print log begin
    Serial.println("Log begins");
    
    
    //calculate the length between the input and print out data.
    for(int i = 0; i < dataLength-1; i++){
      interruptLength[i] = interruptTime[i+1]-interruptTime[i];
      Serial.print(interruptLength[i]);
      Serial.print(" - ");
      Serial.println(interruptState[i+1]);
    }
    
    //print end of log
    Serial.println("Log ends");
    
    
    //clear all data
    for(int i = 0; i < dataLength + 1; i++){
      interruptLength[i] = 0;
      interruptTime[i] = 0;
      interruptState[i] = 0;
    }
    
    dataLength = 0;
    //clear serial buffer
    int data = Serial.available();
    for(int i = 0; i<data; i++){
      temp = Serial.read();
    }
  }
      
}


// -------------------------------------------------------
// Interrupt Event Handler
// -------------------------------------------------------
void interruptPinChange(){
  noInterrupts();
  
  // Log the time of the interrupt
  interruptTime[dataLength] = micros();
  
  // Record the pin state
  interruptState[dataLength] = (digitalRead(interruptPin) == HIGH);
  
  // Increment the length of the data log
  dataLength++;
  
  interrupts();
  
}
