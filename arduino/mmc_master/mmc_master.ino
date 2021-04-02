//initialize all global variables
int valvepins[] = {2, 3, 4, 5}; //output pins for reward valves 1, 2, 3, and 4
int sensorpins[] = {0, 1, 2, 3}; // input pins for nosepoke detector 1, 2, 3, and 4
uint8_t sensorvals[] = {0, 0, 0, 0}; // variable to store the values coming from the sensors
int i = 0;
uint8_t instruction, disloc, rewardloc;

void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps

  //set the valve pins to output and closes them (want to make sure they're closed at the start)
  for (i = 0; i <= 3; i++) {
    pinMode(valvepins[i], OUTPUT);    // sets the digital pin as output
    digitalWrite(valvepins[i], LOW);  // sets the digital pin low = closed? 
  } 

  //////////set the sensor pins to input here
  for (i = 0; i <= 3; i++) {
    pinMode(sensorpins[i], INPUT);
  }
}

//read serial message
uint8_t readSerialMessage() {
  int msg16 = Serial.read();
  uint8_t msg = 0;
  if (msg16!=-1) {
    msg = msg16;
  }
  return msg;
}

void loop() {
  //////////////wait for incoming instructions over serial
  wait4Serial(1); 
  instruction = readSerialMessage(); 
  
  switch (instruction) {
    case 100: //show display
       wait4Serial(1); 
       disloc = readSerialMessage(); 
       
          switch(disloc){
            case 0: //cue position 
               //show display at cue
            break;
            
            case 1: //display 1
              //show display at 1
            break;
            
            case 2: //display 2
              //show display at 2
            break;

            case 3: //display 3
              //show display at 3
            break;
          }
      break; //finish showing display

    case 101: //reward at display
       wait4Serial(1); 
       rewardloc = readSerialMessage();

       digitalWrite(valvepins[rewardloc], HIGH); //open valve at rewardloc
       delay(1000); //keep valve 0 open for 1000 ms
       digitalWrite(valvepins[rewardloc], LOW); //close valve at rewardloc
          
     break; //finish reward
  }
  
  //////read all 4 sensor signals (the values will go high for nose pokes)
  for (int i = 0; i <= 3; i++) {
    sensorvals[i] = analogRead(sensorpins[i]);
    if (sensorvals[i] < 128) {
      Serial.write(10+i); //send poke location
    }
  }
}

//wait for desired amount of available serial data bytes
void wait4Serial(int num2wait4) {
  int bytesavail = Serial.available();
  while (bytesavail<num2wait4) {
    delay(100); //wait 100 ms before checking again
    bytesavail = Serial.available();
  }
}
