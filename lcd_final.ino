#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

// Initialize Bluetooth module on TX/RX
SoftwareSerial BTserial(0, 1); // RX, TX (pins 0 and 1)

// Initialize LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// Relay pins
int relayLightPin1 = 9;        // Table room light
int relayLightPin2 = 10;       // Study light
int relayWooferPin = 11;       // Woofer
int relayBathroomLightPin = 12; // Bathroom light
int relaySnakeLightPin = 13;   // Snake light

// Track light and woofer states
bool light1State = false;
bool light2State = false;
bool wooferState = false;
bool bathroomState = false;
bool snakeState = false;

void setup() {
    // Set relay pins as OUTPUT
    pinMode(relayLightPin1, OUTPUT);
    pinMode(relayLightPin2, OUTPUT);
    pinMode(relayWooferPin, OUTPUT);
    pinMode(relayBathroomLightPin, OUTPUT);
    pinMode(relaySnakeLightPin, OUTPUT);

    Serial.begin(9600);
    BTserial.begin(9600);
  
    // Initialize LCD
    lcd.begin(16, 2);
    
    // Show welcome messages
    lcd.print("Hello Eng. Joe");
    delay(2000); // Display message for 2 seconds
    lcd.clear();

    lcd.print("Welcome To");
    lcd.setCursor(0, 1);
    lcd.print("Project JP");
    delay(3000); // Display for 3 seconds
    lcd.clear();
}

void loop() {
    if (Serial.available()) {
        String command = Serial.readStringUntil('\n');
        processCommand(command);
        updateLCD();
    }

    if (BTserial.available()) {
        char receivedChar = BTserial.read();
        Serial.println(receivedChar);
        processBluetoothCommand(receivedChar);
        updateLCD();
    }
}

void processCommand(String command) {
    if (command == "JP table room light off") {
        digitalWrite(relayLightPin1, LOW);
        light1State = false;
    } else if (command == "JP table room light on") {
        digitalWrite(relayLightPin1, HIGH);
        light1State = true;
    } else if (command == "JP study light on") {
        digitalWrite(relayLightPin2, HIGH);
        light2State = true;
    } else if (command == "JP study light off") {
        digitalWrite(relayLightPin2, LOW);
        light2State = false;
    } else if (command == "JP woofer on") {
        digitalWrite(relayWooferPin, HIGH);
        wooferState = true;
    } else if (command == "JP woofer off") {
        digitalWrite(relayWooferPin, LOW);
        wooferState = false;
    } else if (command == "JP bathroom light on") {
        digitalWrite(relayBathroomLightPin, HIGH);
        bathroomState = true;
    } else if (command == "JP bathroom light off") {
        digitalWrite(relayBathroomLightPin, LOW);
        bathroomState = false;
    } else if (command == "JP snake light on") {
        digitalWrite(relaySnakeLightPin, HIGH);
        snakeState = true;
    } else if (command == "JP snake light off") {
        digitalWrite(relaySnakeLightPin, LOW);
        snakeState = false;
    }
    // Add new "all off" command
    else if (command == "JP all off") {
        // Turn off all relays and reset states
        digitalWrite(relayLightPin1, LOW);
        digitalWrite(relayLightPin2, LOW);
        digitalWrite(relayWooferPin, LOW);
        digitalWrite(relayBathroomLightPin, LOW);
        digitalWrite(relaySnakeLightPin, LOW);
        
        light1State = false;
        light2State = false;
        wooferState = false;
        bathroomState = false;
        snakeState = false;
    }
    // Add new "all on" command
    else if (command == "JP all on") {
        // Turn on all relays and update states
        digitalWrite(relayLightPin1, HIGH);
        digitalWrite(relayLightPin2, HIGH);
        digitalWrite(relayWooferPin, HIGH);
        digitalWrite(relayBathroomLightPin, HIGH);
        digitalWrite(relaySnakeLightPin, HIGH);
        
        light1State = true;
        light2State = true;
        wooferState = true;
        bathroomState = true;
        snakeState = true;
    }
}

void processBluetoothCommand(char receivedChar) {
    if (receivedChar == '1') {
        digitalWrite(relayLightPin2, HIGH);
        light2State = true;
    } else if (receivedChar == '0') {
        digitalWrite(relayLightPin2, LOW);
        light2State = false;
    } else if (receivedChar == '2') {
        digitalWrite(relayLightPin1, HIGH);
        light1State = true;
    } else if (receivedChar == '3') {
        digitalWrite(relayLightPin1, LOW);
        light1State = false;
    } else if (receivedChar == '5') {
        digitalWrite(relayWooferPin, HIGH);
        wooferState = true;
    } else if (receivedChar == '4') {
        digitalWrite(relayWooferPin, LOW);
        wooferState = false;
    } else if (receivedChar == '6') {
        digitalWrite(relayBathroomLightPin, HIGH);
        bathroomState = true;
    } else if (receivedChar == '7') {
        digitalWrite(relayBathroomLightPin, LOW);
        bathroomState = false;
    } else if (receivedChar == '8') {
        digitalWrite(relaySnakeLightPin, HIGH);
        snakeState = true;
    } else if (receivedChar == '9') {
        digitalWrite(relaySnakeLightPin, LOW);
        snakeState = false;
    }
}

// Function to update the LCD display
void updateLCD() {
    lcd.clear();
    int countOn = 0;

    // Count active devices
    if (light1State) countOn++;
    if (light2State) countOn++;
    if (wooferState) countOn++;
    if (bathroomState) countOn++;
    if (snakeState) countOn++;

    lcd.setCursor(0, 0);
    if (countOn == 0) {
        lcd.print("Hey Joe, All Off");
    } else if (countOn == 5) {
        lcd.print("Hey Joe, All ON");
    } else if (countOn >= 2) {
        lcd.print("Hey Joe, " + String(countOn) + " ON");
    } else {
        // Show individual names for 1 ON
        if (light1State) lcd.print("TableLight ON ");
        if (light2State) lcd.print("StudyLight ON ");
        if (wooferState) lcd.setCursor(0, 1), lcd.print("Woofer ON ");
        if (bathroomState) lcd.setCursor(0, 1), lcd.print("BathroomLight ON ");
        if (snakeState) lcd.setCursor(0, 1), lcd.print("SnakeLight ON ");
    }
}
