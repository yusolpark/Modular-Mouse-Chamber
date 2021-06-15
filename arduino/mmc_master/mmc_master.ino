//initialize all global variables
uint8_t valvepins[] = {2, 3, 4, 5}; //output pins for reward valves 1, 2, 3, and 4
uint8_t sensorpins[] = {0, 1, 2, 3}; // input pins for nosepoke detector 1, 2, 3, and 4
uint8_t sensorvals[] = {0, 0, 0, 0}; // variable to store the values coming from the sensors
<<<<<<< HEAD
int i = 0;
uint8_t instruction, disloc, rewardloc;
=======
uint8_t instruction, pos;
>>>>>>> 3e203279e4fec810700cd3a169c7bbe5e5011269

void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps

  //set the valve pins to output and closes them 
  for (pos = 0; pos <= 3; pos++) {
    pinMode(valvepins[pos], OUTPUT);    // sets the digital pin as output
    digitalWrite(valvepins[pos], LOW);  // sets the digital pin low = closed
  } 

  //set sensor pins to input
  for (pos = 0; pos <= 3; pos++) {
    pinMode(sensorpins[pos], INPUT);
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
  //check for incoming instructions over serial
  if (Serial.available()>0) {
    instruction = readSerialMessage(); 
    switch (instruction) {
      case 101: //reward at position
         wait4Serial(1); 
         pos = readSerialMessage();
  
         digitalWrite(valvepins[pos], HIGH); //open valve at position
         delay(1000); //keep valve open for 1000 ms
         digitalWrite(valvepins[pos], LOW); //close valve
            
       break; //finish reward
    }
  }
  
<<<<<<< HEAD
  //////read all 4 sensor signals (the values will go high for nose pokes)
  for (int i = 0; i <= 3; i++) {
    sensorvals[i] = analogRead(sensorpins[i]);
    if (sensorvals[i] < 128) {
      Serial.write(10+i); //send poke location
    }
  }
=======
  //read all 4 sensor signals (the values will go low during nose pokes)
  for (int pos = 0; pos <= 3; pos++) {
    sensorvals[pos] = analogRead(sensorpins[pos]);
    if sensorvals[pos] < 128 {
      Serial.write(10); //send poke position instruction byte
      Serial.write(pos); //send poke position
    }
  }
  delay(1);
>>>>>>> 3e203279e4fec810700cd3a169c7bbe5e5011269
}

//wait for desired amount of available serial data bytes
void wait4Serial(int num2wait4) {
  int bytesavail = Serial.available();
  while (bytesavail<num2wait4) {
    delay(100); //wait 100 ms before checking again
    bytesavail = Serial.available();
  }
}
