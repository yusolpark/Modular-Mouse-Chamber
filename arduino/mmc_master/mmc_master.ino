//initialize all global variables
int valvepins[] = {2, 3, 4, 5}; //output pins for reward valves 1, 2, 3, and 4
int sensorpins[] = {0, 1, 2, 3}; // input pins for nosepoke detector 1, 2, 3, and 4
uint8_t sensorvals[] = {0, 0, 0, 0}; // variable to store the values coming from the sensors
int i = 0;
//any more variables?

void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps

  //set the valve pins to output and closes them (want to make sure they're closed at the start)
  for (i = 0; i <= 3; i++) {
    pinMode(valvepins[i], OUTPUT);    // sets the digital pin as output
    digitalWrite(valvepins[i], HIGH);  // sets the digital pin high
  } 

  //////////set the sensor pins to input here
}

void loop() {
  //////////////wait for incoming instructions over serial

  //////////////if the instruction is to wait for nose pokes, do that

  //////////////if the instruction is to reward a position, do that here


  ///////example code to read serial data and see what it says
  wait4Serial(1); //this function waits until at least 1 byte of serial data is detected
  instruction = readSerialMessage(); //reads the 1st byte of serial data it detects
  switch (instruction) {
    case 1: //if the instruction byte was "1"
      //do thing 1
      break; //finish doing thing 1

    case 2: //if the instruction byte was "2"
      //do thing 2
      break; //finish doing thing 2

    //etc
  }
  
  //////example code to read all 4 sensor signals (the values will go high for nose pokes)
  for (int i = 0; i <= 3; i++) {
    sensorvals[i] = analogRead(sensorpins[i]);
  }


  //////example code to give a reward at a position that detected a nose pokeves, turns on/off backlights, sends serial data corresponding to sensor signals
  for (int i = 0; i <= 3; i++) { //loop for all 4 positions
    if (sensorvals[i] < 512) {
      digitalWrite(valvepins[i], HIGH); //open valve
      delay(1000); //keep valve i open for 1000 ms
      digitalWrite(valvepins[i], LOW); //close valve
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
