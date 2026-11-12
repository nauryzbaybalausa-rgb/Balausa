volatile int controlSum = 0;

__attribute__((noinline))
void memoryHog(uint8_t level) {
  volatile int buffer[300];  // 300 × 2 байта ≈ 600 байт

  for (int i = 0; i < 300; i++) {
    buffer[i] = i + level;
  }

  Serial.print("level = ");
  Serial.println(level);

  if (level > 0) {
    memoryHog(level - 1);
  }

  controlSum += buffer[level];
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("MEMORY HOG START");
  memoryHog(4);
  Serial.println("MEMORY HOG FINISH");
}

void loop() {}

