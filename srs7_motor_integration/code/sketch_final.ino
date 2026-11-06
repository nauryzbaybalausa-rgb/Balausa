const int buttonPin = 2;    
const int trigPin = 9;       
const int echoPin = 10;      

const int redLedPin = 13;
const int yellowLedPin = 12;
const int greenLedPin = 11;

const int motorForwardPin = 5;
const int motorReversePin = 6;
const int motorEnaPin = 3;

int buttonState;             
int lastButtonState = HIGH;  
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 30; 

bool systemActive = false;

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
  
  buttonState = digitalRead(buttonPin);
  Serial.begin(9600);
  Serial.println("Система в режиме ожидания. Нажмите кнопку для запуска.");
}

bool readDistanceSafe(long &outDistance) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH, 30000);
  
  if (duration == 0) {
    outDistance = 0;
    return false;
  }
  
  long cm = duration * 0.034 / 2;
  
  if (cm < 2 || cm > 400) {
    outDistance = 0;
    return false;
  }
  
  outDistance = cm;
  return true;
}

void loop() {
  int reading = digitalRead(buttonPin);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      
      if (buttonState == LOW) {
        systemActive = !systemActive;
        if (systemActive) {
          Serial.println(">>> Кнопка нажата: Система ЗАПУЩЕНА!");
        } else {
          Serial.println(">>> Кнопка нажата: Система НА ПАУЗЕ!");
        }
      }
    }
  }
  lastButtonState = reading;

  if (!systemActive) {
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(motorForwardPin, LOW);
    digitalWrite(motorReversePin, LOW);
    analogWrite(motorEnaPin, 0);
    delay(50);
    return; 
  }

  long distance = 0;
  bool isValid = readDistanceSafe(distance);
  
  if (!isValid) {
    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(motorForwardPin, LOW);
    digitalWrite(motorReversePin, LOW);
    analogWrite(motorEnaPin, 0);
    
    Serial.println("Ошибка датчика: тайм-аут. Безопасный стоп.");
    delay(200);
    return;
  }
  
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
  
  delay(250);
}
