//declare pin variables
short button = 23, ledIn=LED_BUILTIN, photo = A5, ledGreen=D2, ledBlue=D15, relay = D8, trig=D6, echo=D7 ;

//function variables
boolean relayState=0, relayLock=0;
double seconds;
short ultra1, ultra2;
int luminanceR;

//declare functions
void setRelay(bool state);
void toggleLedBlue();
void toggleLedGreen();
int getProximity();
short getPhoto();


void setup() {
  //start the serial monitor with baud rate of 115200
  Serial.begin(9600);
  
  // initialize all the pins with respective I/O type
  pinMode(button, INPUT);
  pinMode(ledIn, OUTPUT);
  pinMode(photo, INPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(relay, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
}

void loop() {
  
  /*Serial.print("Button State: ");
  Serial.print(digitalRead(button));
  Serial.println(); */
  
  //toggle the relay with the button and lock the relay for 15 minutes
  

  //check time to disable relaylock and turn off light
  if (seconds>45) {
    relayLock=false;
    setRelay(false);
    
  }
  
  
 /* Serial.print("Relay State & Toggle: ");
  toggleRelay();
  Serial.print(relayState);
  Serial.println();*/

  
  ultra1 = getProximity(); //saves first distance in cm
  delay(350); //delay loop by 250ms and print seconds value
  Serial.print("Seconds elapsed: ");
  Serial.print(seconds);
  Serial.println();
  ultra2 = getProximity(); //saves 2nd dsiatnce in cm
  seconds += .5;
  
  //turnon blue led for motion detection
  ultra2 -= ultra1;
  Serial.println(ultra2);
  if (ultra2 > 10 || ultra2 < -10) {
    toggleLedBlue();

    if (!relayLock) {
      setRelay(true);
      seconds=0;
    }
  }

  //print out luminance in lux
  luminanceR = getPhoto()*20;
  Serial.print("Luminance level (lux): ");
     Serial.print(analogRead(photo));
     Serial.println();
       
  //turnon greenled for light detection DARK
  if (getPhoto()<20) { 
   toggleLedGreen();
  }
  
  
}


//sets the relay
void setRelay(bool state) {
  if (state) {
   pinMode(relay,OUTPUT);
   relayState=1;
  } else {
    pinMode(relay,INPUT);
    relayState=0;
  }
}

//toggles the blue led
void toggleLedBlue() {
  if (digitalRead(ledBlue)==HIGH) {
    digitalWrite(ledBlue, LOW);
  } else {
    digitalWrite(ledBlue, HIGH);
  }
}

//toggles the green led
void toggleLedGreen() {
  if (digitalRead(ledGreen)==HIGH) {
    digitalWrite(ledGreen, LOW);
  } else {
    digitalWrite(ledGreen, HIGH);
  }
}

short getPhoto() {
  return analogRead(photo);
}

int getProximity() {
  //local vars
  long duration;
  int distance;
  
  // Clears the trigPin condition
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echo, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}
