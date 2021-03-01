#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd = LiquidCrystal(9, 8, 4, 5, 6, 7); // Create an LCD object.
// Parameters: (RS, E, D4, D5, D6, D7)
const int TRIG_PIN = 3;
const int ECHO_PIN = 2;
const int SERVO_PIN = 10;
const int DISTANCE_THRESHOLD1 = 50;
const int DISTANCE_THRESHOLD2 = 80; //cm

Servo servo; //create a servo object

float duration_us, distance_cm;
unsigned int counter = 10;
bool bottle_empty = false;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  servo.attach(10);
  servo.write(0);
  lcd.begin(16, 2);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration_us = pulseIn(ECHO_PIN, HIGH);
  distance_cm = 0.017 * duration_us; //calculate the distance
	
  
  if (!bottle_empty) {
    if (distance_cm >= DISTANCE_THRESHOLD1 && distance_cm <= DISTANCE_THRESHOLD2 && counter != 0) {

    if (servo.read() != 0) {
      Serial.print("counter: ");
      Serial.print(counter);
      Serial.print("\n");
  	  servo.write(0);
      counter--;
      lcd.setCursor(0, 0);
      lcd.print("Thank You  ");
      lcd.setCursor(0, 1);
      lcd.print("Stay Safe   ");
    }
  } else {
    servo.write(90);
  	lcd.setCursor(0, 0);
    lcd.print("Bring Your");
    lcd.setCursor(0, 1);
    lcd.print("Hands Closer");
  	}
  }
  // For LCD Display

  if (counter == 0) {
    bottle_empty = true;
    lcd.setCursor(0, 0);
    lcd.print("Bottle Empty! ");
    lcd.setCursor(0, 1);
    lcd.print("Please Refill.");
  }

/*Serial.print("distance:  ");
  Serial.print(distance_cm);
  Serial.println(" cm");
*/
  delay(500);

}