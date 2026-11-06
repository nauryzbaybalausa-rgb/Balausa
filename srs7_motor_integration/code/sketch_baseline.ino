const int buttonPin = 2;
const int trigPin = 9;
const int echoPin = 10;

const int redLedPin = 13;
const int yellowLedPin = 12;
const int greenLedPin = 11;

const int motorForwardPin = 5;
const int motorReversePin = 6;
const int motorEnaPin = 3;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  
  pinMode(motorForwardPin, OUTPUT);
  pinMode(motorReversePin, OUTPUT);
  pinMode(motorEnaPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  
  if (buttonState == HIGH) {
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(motorForwardPin, LOW);
    digitalWrite(motorReversePin, LOW);
    analogWrite(motorEnaPin, 0);
    
    Serial.println("Кнопка отпущена. Система ожидает.");
    delay(200);
    return;
  }
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH, 30000);
  
  if (duration == 0) {
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(motorForwardPin, LOW);
    digitalWrite(motorReversePin, LOW);
    analogWrite(motorEnaPin, 0);
    
    Serial.println("Ошибка датчика: тайм-аут эха. Безопасный стоп.");
    delay(200);
    return;
  }
  
  long distance = duration * 0.034 / 2;
  
  Serial.print("Расстояние: ");
  Serial.print(distance);
  Serial.println(" см");
  
  if (distance < 20) {
    digitalWrite(redLedPin, HIGH);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
    
    digitalWrite(motorForwardPin, LOW);
    digitalWrite(motorReversePin, LOW);
    analogWrite(motorEnaPin, 0);
  } 
  else if (distance >= 20 && distance <= 50) {
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
    
    digitalWrite(motorForwardPin, HIGH);
    digitalWrite(motorReversePin, LOW);
    analogWrite(motorEnaPin, 120);
  } 
  else {
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
    
    digitalWrite(motorForwardPin, HIGH);
    digitalWrite(motorReversePin, LOW);
    analogWrite(motorEnaPin, 255); 
  }
  
  delay(100);
}
