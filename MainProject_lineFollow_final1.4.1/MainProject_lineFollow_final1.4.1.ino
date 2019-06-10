//White background = LOW, Black background = HIGH
int rEnablePin =11; //right enable pin; the right enable pin on the h bridge is connected to pin 11 on the arduino
int lEnablePin =10; // left enable pin
int lPin1 = 6; // left transistor(h bridge) pin top; pin "10" in the diagram; In3
int lPin2 = 7; // left transistor pin bottom; IN4
int rPin1 = 4; // right transistor pin top; IN2
int rPin2 = 5; // right transistor pin bottom: IN1 because our h bridge is upside down
//line sensor
int sensorR = 2; //the right sensor( we are using two sensors) 
int sensorL = 3; //the left sensor
unsigned long previousMillis = 0; // might delete doesn't do anything
bool stateR = false; //should it turn? //state R means the state of the right sensor; false means staring at white paper; true is staring at black paper
bool stateL = false;// it is set to false in the beginning so it knows to start driving straight
int SPEED = 200;// it could be between 0 and 255, we needed it to be slower than max speed because it was going crazy
int TURNTIME = 1000;// the time it takes for it to turn
void setup() //this is one of the 2 main functions; first one to run; only runs once
{
  Serial.begin (9600); //Sets the data rate to 9600 bits per second for serial data transmission
  pinMode(rEnablePin, OUTPUT);// the arduino is outputting( voltage/current) to the h bridge
  pinMode(lEnablePin, OUTPUT);
  pinMode(lPin1, OUTPUT);
  pinMode(lPin2, OUTPUT);
  pinMode(rPin1, OUTPUT);
  pinMode(rPin2, OUTPUT);
  pinMode(sensorR, INPUT); // input means we are receiving a signal from it
  pinMode(sensorL, INPUT);// it receives a high or low voltage
}
 // test all functions and remember speed can only be between 0 and 255
void loop()  //this is the other main function
{
 
  if(turnStateR() && !turnStateL()){ //turnstateR returns a value of true or false; if R true and L is false it will turn left
    //turn left when right sensor is triggered //true means black
    rightWheelForward(SPEED);//the speed was defined at the top (200) we can change manually
    leftWheelBackward(SPEED);
  }else if(turnStateL() && !turnStateR()){ //same but reverse
     //turn right when left sensor is triggered
    leftWheelForward(SPEED);
    rightWheelBackward(SPEED);
  }
  else if(turnStateL() && turnStateR()){ //when both of them are true means it hits a black line and it stops
     //turn right when left sensor is triggered
    leftWheelForward(0);// this is the one in the front
    rightWheelForward(0);
  }else{
    rightWheelForward(SPEED); //will change to the drive forward function
    leftWheelForward(SPEED);
    
  }
  Serial.print(digitalRead(sensorR)); //gives information of what the sensors are doing
  Serial.println(digitalRead(sensorL));// output in the serial monitor as 0 or 1
}

bool turnStateR(){ //if its high then it will change to true
  if(digitalRead(sensorR) == 1){
    stateR = true;
  }
  if(digitalRead(sensorR) == 0){// it its low it will change to false
    stateR = false;
  }
  return stateR; 
}
bool turnStateL(){ // same thing as above
  if(digitalRead(sensorL) == 1){
    stateL = true;
  }
  if(digitalRead(sensorL) == 0){
    stateL = false;
  }
  return stateL;// means this bool function is returning that value for it to go into the true or false


void leftWheelForward(int speed){
  //spins left wheel to drive forward
  analogWrite(lEnablePin, speed);
  digitalWrite(lPin1, LOW);
  digitalWrite(lPin2, HIGH);
}

// test these functions
void leftWheelBackward(int speed){
  //spins left wheel to drive backwards
  analogWrite(lEnablePin, speed);
  digitalWrite(lPin1, HIGH);
  digitalWrite(lPin2, LOW);
}

// test to see if it does this
void rightWheelForward(int speed){
  //spins right wheel to drive forward
  analogWrite(rEnablePin, speed);
  digitalWrite(rPin1, HIGH);
  digitalWrite(rPin2, LOW);
}

//test to see if it does this
void rightWheelBackward(int speed){
  //spins right wheel to drive Backwards
  analogWrite(rEnablePin, speed);
  digitalWrite(rPin1, LOW);
  digitalWrite(rPin2, HIGH);
}

// test after you have tested everything else, remember time is in milliseconds, try 5000 just to make sure it's working
void driveForward(int speed)
{
  
  leftWheelForward(speed);
  rightWheelForward(speed);
  leftWheelBackward(0);
  rightWheelBackward(0);
}

void driveBackward(int speed, int time)
{
  leftWheelBackward(speed);
  rightWheelBackward(speed);
  //turn off motors
  leftWheelForward(0);
  rightWheelForward(0); //
}

