const int ledPin = 2;
unsigned long prev = 0;

enum { S_SHORT1, S_SHORT2, S_SHORT3, O_LONG1, O_LONG2, O_LONG3, S_SHORT4, S_SHORT5, S_SHORT6, PAUSE };
int state = S_SHORT1;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long now = millis();

  switch(state) {
    case S_SHORT1:
    case S_SHORT2:
    case S_SHORT3:
    case S_SHORT4:
    case S_SHORT5:
    case S_SHORT6:
      digitalWrite(ledPin, HIGH);
      if(now - prev >= 200) {
        prev = now;
        digitalWrite(ledPin, LOW);
        state++;
      }
      break;
      
    case O_LONG1:
    case O_LONG2:
    case O_LONG3:
      digitalWrite(ledPin, HIGH);
      if(now - prev >= 600) {
        prev = now;
        digitalWrite(ledPin, LOW);
        state++;
      }
      break;
      
    case PAUSE:
      if(now - prev >= 2000) {
        prev = now;
        state = S_SHORT1;
      }
      break;
  }
}