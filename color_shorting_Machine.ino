#include <Servo.h>
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6
Servo topServo;
Servo bottomServo;

int frequency = 0;
int color=0;
int unknownCount = 0;

void setup() {
  pinMode(S0, OUTPUT);      //initializing the pins of the arduino with the sensor
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Setting  the frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  topServo.attach(7);
  bottomServo.attach(8);
  Serial.begin(9600);
}
void loop() {
  topServo.write(115);
  delay(1000);
  
  for(int i = 115; i > 65; i--) {
    topServo.write(i);
    delay(2);
  }
  delay(1000);
  
  color = readColor();
  delay(100);  
  switch (color) {
  case 1:
    Serial.println("Color detected: RED");
    bottomServo.write(105);
    unknownCount = 0;
    break;

  case 2:
    Serial.println("Color detected: BLUE");
    bottomServo.write(170);
    unknownCount = 0;
    break;

  default:
    Serial.println("Color detected: UNKNOWN");
    unknownCount++;
    break;
}


if (unknownCount >= 3) {
  Serial.println("STOP: 3 UNKNOWN DETECTED!!!!!!!!!!!   NO CANDY  LEFT!!!!!!!!");
  topServo.write(90);   // neutral position in the case of no candy recognised
  while (1);           
}

  delay(500);
  
  for(int i = 55; i > 45; i--) {
    topServo.write(i);
    delay(5);
  } 
  delay(200);
  
  for(int i = 45; i < 80; i++) {
    topServo.write(i);
    delay(5);
  }
  color=0;
}

// Custom Function  for reading the colors using the sensor
int readColor() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing R
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing G
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(70);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing B
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(70);

if (R >= 70 && R <= 100 && G >= 140 && G <= 165 && B >= 115 && B <= 150) {
  color = 1; // RED
}
else if (R >= 115 && R <= 150 && G >= 105 && G <= 135 && B >= 60  && B <= 95) {
  color = 2; // BLUE
}
return color;
}


