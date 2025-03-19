#include <SoftwareSerial.h>

SoftwareSerial BTserial(0, 1); // RX, TX (pins 0 and 1)

int relayLightPin1 = 9;       // Table room light relay
int relayLightPin2 = 10;      // study light relay
int relayWooferPin = 11;         // woofer relay
int relayBathroomLightPin = 12; // Bathroom light relay
int relaySnakeLightPin = 13; // snake light light relay

void setup() {
    pinMode(relayLightPin1, OUTPUT); 
    pinMode(relayLightPin2, OUTPUT);
    pinMode(relayWooferPin, OUTPUT);
    pinMode(relayBathroomLightPin, OUTPUT);
    pinMode(relaySnakeLightPin, OUTPUT);

    Serial.begin(9600); // Initialize serial communication for debugging
    BTserial.begin(9600); // Initialize Bluetooth communication
}

void loop() {
    // Check for voice commands
    if (Serial.available()) {
        String command = Serial.readStringUntil('\n'); // Read the incoming command
        processCommand(command);
    }

    // Check for Bluetooth button commands
    if (BTserial.available()) {
        char receivedChar = BTserial.read(); // Read the incoming character
        Serial.println(receivedChar); // Print the received character for debugging
        processBluetoothCommand(receivedChar);
    }
}

void processCommand(String command) {
    if (command == "JP table room light off") {
        digitalWrite(relayLightPin1,LOW ); 
    } else if (command == "JP table room light on") {
        digitalWrite(relayLightPin1, HIGH); 
    } else if (command == "JP study light on") {
        digitalWrite(relayLightPin2, HIGH); 
    } else if (command == "JP study light off") {
        digitalWrite(relayLightPin2, LOW); 
    } else if (command == "JP woofer on") {
        digitalWrite(relayWooferPin, HIGH); 
    } else if (command == "JP woofer off") {
        digitalWrite(relayWooferPin, LOW); 
    } else if (command == "JP bathroom light on") {
        digitalWrite(relayBathroomLightPin, HIGH); 
    } else if (command == "JP bathroom light off") {
        digitalWrite(relayBathroomLightPin, LOW); 
    } else if (command == "JP snake light on") {
        digitalWrite(relaySnakeLightPin, HIGH); 
    } else if (command == "JP snake light off") {
        digitalWrite(relaySnakeLightPin, LOW); 
    }
}

void processBluetoothCommand(char receivedChar) {
    if (receivedChar == '1') {
        digitalWrite(relayLightPin2, HIGH); // study light OFF
    } else if (receivedChar == '0') {
        digitalWrite(relayLightPin2, LOW); // study light ON
    } else if (receivedChar == '2') {
        digitalWrite(relayLightPin1, HIGH); // Table room light OFF
    } else if (receivedChar == '3') {
        digitalWrite(relayLightPin1, LOW); // Table room light ON
    } else if (receivedChar == '5') {
        digitalWrite(relayWooferPin, HIGH); // woofer OFF
    } else if (receivedChar == '4') {
        digitalWrite(relayWooferPin, LOW); // woofer ON
    } else if (receivedChar == '6') {
        digitalWrite(relayBathroomLightPin, HIGH); // Bathroom light OFF
    } else if (receivedChar == '7') {
        digitalWrite(relayBathroomLightPin, LOW); // Bathroom light ON
    } else if (receivedChar == '8') {
        digitalWrite(relaySnakeLightPin, HIGH); // snake light OFF
    } else if (receivedChar == '9') {
        digitalWrite(relaySnakeLightPin, LOW); // snake light ON
    }
}
