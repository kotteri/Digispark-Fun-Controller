#define MOTOR_PIN 1 /* outside pin */
#define START_SW 0
#define SPEAKER_PIN 2

int state = 0;
int Pwm;
unsigned long time;
    
void setup()
{
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(START_SW, INPUT_PULLUP);
  pinMode(SPEAKER_PIN, OUTPUT);


  analogWrite(MOTOR_PIN, 255);
  state = 5;
  Pwm = 255;

  time = millis();
}


void loop() {

  if (state == 0 && digitalRead(START_SW) == LOW) {
    Pwm = 255; // とりあえず仮の値
    analogWrite(MOTOR_PIN, Pwm);
    state = 5;
    time = millis();
  }
  
  if (state == 5) {
    if (millis() - time > 600000UL) { // 10分後
      analogWrite(MOTOR_PIN, 40); // めいっぱい遅く

    } else if (millis() - time > 120000UL) { // 2分後
      analogWrite(MOTOR_PIN, 120); // まあまあ遅く
    }
  }
  
  if (state > 0 && digitalRead(START_SW) == LOW) {
    
    
    state--;
    if (state == 0) {
      Pwm = 0;
      analogWrite(MOTOR_PIN, Pwm);
      beep(SPEAKER_PIN, 880, 30);
      delay(50);
      beep(SPEAKER_PIN, 440, 50);
      
    } else {
      
      switch (state) {
        case 4:
          analogWrite(MOTOR_PIN, 180);
          break;
        case 3:
          analogWrite(MOTOR_PIN, 120);
          break;
        case 2:
          analogWrite(MOTOR_PIN, 70);
          break;
        case 1:
          analogWrite(MOTOR_PIN, 40);
          break;
      }
      beep(SPEAKER_PIN, 880, 30);
    }
    
    delay(300);
  } 
  
  if (state > 0 && millis() - time > 2400000UL) { // 40分後
    analogWrite(MOTOR_PIN, 0); // stop
    state = 0;

    beep(SPEAKER_PIN, 880, 50);
    delay(100);
    beep(SPEAKER_PIN, 880, 50);
    delay(100);
    beep(SPEAKER_PIN, 880, 50);
    delay(100);
    beep(SPEAKER_PIN, 880, 50);
    
  }

  delay (200);
}

void beep(int pin, int frequency, int len) {
  unsigned int t = 250000 / frequency;
  if (t < 1) t = 1;
  for (unsigned int i = 0; i < frequency / 250 * len; i++) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(t);
    digitalWrite(pin, LOW);
    delayMicroseconds(t);
  }
}
