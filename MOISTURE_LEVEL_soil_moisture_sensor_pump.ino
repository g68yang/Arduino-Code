// Declare variables for pins
const int sensorpin = A0;
const int sensorpower = 8;
const int LED1 = 2;
const int LED2 = 3;
const int LED3 = 4;
const int pumppin = 11;

// Variable for sensor reading
int sensor;

// Delay time between sensor readings (milliseconds)
const int delayTime = 1000;  // Increased for stability

// Default thresholds for Lemon Plant
int wet = 800;
int dry = 500;

// Variable to store received plant type
String plantType = "";

void setup() { 
    // Set pins as outputs
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(sensorpower, OUTPUT);
    pinMode(pumppin, OUTPUT);
    
    // Initialize serial communication
    Serial.begin(9600);
}

void loop()
{
    // analogRead function returns the integer 10 bit integer (0 to 1023)
    sensor = analogRead(sensorpin);
  
    // Print text in serial monitor
    Serial.println("Analog value:");
    // Print analog value in serial monitor
    Serial.println(sensor);
}


void loop() { 
    // Read plant type from Raspberry Pi
    if (Serial.available()) {
        plantType = Serial.readStringUntil('\n');  // Read the string until newline
        plantType.trim();  // Remove whitespaces from received string
        Serial.print("Received Plant Type: ");
        Serial.println(plantType);

        // **Adjust Moisture Thresholds Based on Plant Type**
        if (plantType == "Basil") {
            wet = 900;  // Higher moisture requirement
            dry = 600;
            Serial.println("Thresholds Set: Basil (Wet: 900, Dry: 600)");
        } else if (plantType == "Lemon") {
            wet = 800;  // Default Lemon thresholds
            dry = 500;
            Serial.println("Thresholds Set: Lemon (Wet: 800, Dry: 500)");
        } else {
            Serial.println("Unknown Plant Type, Using Default Thresholds.");
        }
    }

    // Power on sensor and wait briefly
    digitalWrite(sensorpower, HIGH);
    delay(10);
    
    // Take reading from sensor
    sensor = analogRead(sensorpin); 
    
    // Turn sensor off to help prevent corrosion
    digitalWrite(sensorpower, LOW);
    
    // Print sensor reading
    Serial.print("Moisture Level: ");
    Serial.println(sensor);
    
    // **Decision Logic Based on Soil Moisture**
    
    // If sensor reading is greater than "wet" threshold, turn on green LED.
    if (sensor > wet) {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, HIGH);
        digitalWrite(pumppin, LOW);
    } 
    // If it is less than the "dry" threshold, turn on red LED and pump.
    else if (sensor < dry) {
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(pumppin, HIGH);
    } 
    // If it is between the two threshold levels, turn on yellow LED.
    else {
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, LOW);
        digitalWrite(pumppin, LOW);
    }

    // Wait before taking next reading
    delay(delayTime);
}
