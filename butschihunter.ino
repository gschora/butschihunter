#include <EEPROMex.h>
#include <SerialCommand.h>

SerialCommand SCmd;

int ledPin = 13;
int laserPin = 6;
int switchPin = 2;
//volatile unsigned long alteZeit = 0, entprellZeit = 20;
bool up = false;
uint8_t laserTime = 1;
uint8_t waitTime = 10;
int val = 0;

int16_t laserTimeAddress; // address in eeprom
int16_t waitTimeAddress;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);    // LED Pin
  pinMode(laserPin, OUTPUT);
  pinMode(switchPin, INPUT);       // Pin 2 ist INT0
  digitalWrite(2, LOW);   // interner Pull up Widerstand auf 5V
  //  attachInterrupt(0, interruptRoutine, HIGH);
  // Pin 2 (INT 0) geht auf 0V (LOW) dann interruptRoutine aufrufen
    
    EEPROM.setMaxAllowedWrites(30);
    EEPROM.setMemPool(0, EEPROMSizeATmega328);
    
    laserTimeAddress = EEPROM.getAddress(sizeof(int));
    waitTimeAddress = EEPROM.getAddress(sizeof(int));
    readInit();
    
    SCmd.addDefaultHandler(unrecognized);
    SCmd.addCommand("setlaser", cmdSetLaserTime);
    SCmd.addCommand("setwait", cmdSetWaitTime);
    SCmd.addCommand("laserswitch", cmdLaserSwitch);
    SCmd.addCommand("getsettings", cmdGetSettings);
}

void loop() {
    SCmd.readSerial();
  val = digitalRead(switchPin);   // read input value and store it in val
  if (val == HIGH) {               // check if the button is pressed
    digitalWrite(ledPin, HIGH);   // turn LED on
    digitalWrite(laserPin, HIGH);
    Serial.println("1");
    delay(laserTime*100);
    digitalWrite(ledPin, LOW);
    digitalWrite(laserPin, LOW);
    delay(waitTime*100);
  }
}

void unrecognized()
{
  Serial.println("command not understood!");
	Serial.println("available commands:");
	Serial.println("setlaser 1 .....=100ms (time in ms / 100)");
	Serial.println("setwait 10 .....=1000ms (time in ms / 100)");
    Serial.println("laserswitch 0 .....switch laser 1=on 0=off");
    Serial.println("getsettings ..... prints the times that are currently set");
	Serial.println("---------------------------------------"); 
}

void cmdSetLaserTime(){
    char *arg = SCmd.next();
	if (arg != NULL) {
		laserTime = atoi(arg);
        EEPROM.update(laserTimeAddress, laserTime);
        readInit();
	}
    
}

void cmdSetWaitTime(){
    char *arg = SCmd.next();
	if (arg != NULL) {
		waitTime = atoi(arg);
        EEPROM.update(waitTimeAddress, waitTime);
        readInit();
	} 
}

void cmdLaserSwitch(){
    char *arg = SCmd.next();
	if (arg != NULL) {
		uint8_t laserSwitch = atoi(arg);
        switch (laserSwitch){
            case 0:
                digitalWrite(ledPin, LOW);   // turn LED on
                digitalWrite(laserPin, LOW);
                Serial.println("laser OFF");
                break;
            case 1:
                digitalWrite(ledPin, HIGH);   // turn LED on
                digitalWrite(laserPin, HIGH);
                Serial.println("laser ON");
                break;
        }
	} 
}

void cmdGetSettings(){
    Serial.println("---------------------------------");
    Serial.println("Current Settings are:");
    Serial.print("laserTime: ");
    Serial.println(laserTime);
    Serial.print("waitTime: ");
    Serial.println(waitTime);
    Serial.println("---------------------------------");
}

void readInit(){
    laserTime = EEPROM.read(laserTimeAddress);
    waitTime = EEPROM.read(waitTimeAddress);
    Serial.println("---------------------------------");
    Serial.println("eeprom_settings: ");
    Serial.print("laserTime: ");
    Serial.println(laserTime);
    Serial.print("waitTime: ");
    Serial.println(waitTime);
    Serial.println("---------------------------------");
}

