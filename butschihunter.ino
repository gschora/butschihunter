#include <SerialCommand.h>

SerialCommand SCmd;

int ledPin = 13;
int laserPin = 6;
int switchPin = 2;
//volatile unsigned long alteZeit = 0, entprellZeit = 20;
bool up = false;
int laserTime = 100;
int waitTime = 1000;
int val = 0;
void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);    // LED Pin
  pinMode(laserPin, OUTPUT);
  pinMode(switchPin, INPUT);       // Pin 2 ist INT0
  digitalWrite(2, LOW);   // interner Pull up Widerstand auf 5V
  //  attachInterrupt(0, interruptRoutine, HIGH);
  // Pin 2 (INT 0) geht auf 0V (LOW) dann interruptRoutine aufrufen
    
    SCmd.addDefaultHandler(unrecognized);
    SCmd.addCommand("setlaser", cmdSetLaserTime);
    SCmd.addCommand("setwait", cmdSetWaitTime);
}

void loop() {
    SCmd.readSerial();
  val = digitalRead(switchPin);   // read input value and store it in val
  if (val == HIGH) {               // check if the button is pressed
    digitalWrite(ledPin, HIGH);   // turn LED on
    digitalWrite(laserPin, HIGH);
    Serial.println("pressed");
    delay(laserTime);
    digitalWrite(ledPin, LOW);
    digitalWrite(laserPin, LOW);
    delay(waitTime);
  }
  if (val == LOW) {              // check if the button is not pressed
    digitalWrite(ledPin, LOW);    // turn LED off
  }
}

void unrecognized()
{
  Serial.println("command not understood!");
	Serial.println("available commands:");
	Serial.println("setlaser");
	Serial.println("setwait");
	Serial.println("---------------------------------------"); 
}

void cmdSetLaserTime(){
    char *arg = SCmd.next();
	if (arg != NULL) {
		laserTime = atoi(arg);
	} 
}

void cmdSetWaitTime(){
    char *arg = SCmd.next();
	if (arg != NULL) {
		waitTime = atoi(arg);
	} 
}
//void interruptRoutine() {
//  if ((millis() - alteZeit) > entprellZeit) {
//    if (!up) {
//      // innerhalb der entprellZeit nichts machen
//      digitalWrite(LED,HIGH); // LED umschalten
//      Serial.println("btn_pressed");
//      digitalWrite(LASERPIN, HIGH);
//      delayMicroseconds(laserTime);
//      digitalWrite(LASERPIN, LOW);
//      digitalWrite(LED, LOW);
//      up = true;
//    } else {
//      up = false;
//    }
//    alteZeit = millis(); // letzte Schaltzeit merken
//  }
//}

