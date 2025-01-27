#include<Servo.h>

int lightval;             // Variable to store the light value read from the light sensor
int lightpin = A0;        // Pin connected to the light sensor
int time = 100;           // Delay time in milliseconds
int servopin = 3;         // Pin connected to the servo motor
Servo myservo;            // Create a servo object
int angle;                // Variable to store the angle of the servo motor

void setup() {
  Serial.begin(9600);           // Initialize the serial communication at 9600 baud rate
  pinMode(lightpin,INPUT);      // Set the light sensor pin as an input
  myservo.attach(servopin);     // Attach the servo motor to the specified pin
  pinMode(servopin,OUTPUT);     // Set the servo motor pin as an output
} 

void loop() {
  lightval = analogRead(lightpin);     // Read the light value from the light sensor
  Serial.println(lightval);            // Print the light value to the serial monitor
  delay(time);                         // Wait for the specified delay time
  
  angle = lightval/5;               // Calculate the angle of the servo motor based on the light value
  myservo.write(angle);             // Write the calculated angle to the servo motor
  Serial.println("angle is");       // Print a message to the serial monitor
  Serial.println(angle);            // Print the calculated angle to the serial monitor
}