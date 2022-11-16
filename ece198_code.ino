//declare pin variables
int button = 23;
int relay = 8;
int seconds=0;

//function variables
boolean relayState=0;

//declare functions
void toggleRelay();

void setup() {
  //start the serial monitor
  Serial.begin(9600);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(button,INPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(500);                       // wait for a second

  Serial.print("Button State: ");
  Serial.print(digitalRead(button));
  Serial.println();

  //toggle the relay with the button
  if (!digitalRead(button)) {
    toggleRelay();
  }
  
  Serial.print("Relay State & Toggle: ");
  toggleRelay();
  Serial.print(relayState);
  Serial.println();
}



void toggleRelay() {
  if (relayState==0) {
   pinMode(relay,OUTPUT);
   relayState=1;
  } else {
    pinMode(relay,INPUT);
    relayState=0;
  }
}
