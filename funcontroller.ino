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
  beep(SPEAKER_PIN, 880, 30);

  time = millis();
}


void loop() {

  if (state == 0 && digitalRead(START_SW) == LOW) {
    Pwm = 255; // とりあえず仮の値
    analogWrite(MOTOR_PIN, Pwm);
    state = 5;
    time = millis();
    beep(SPEAKER_PIN, 880, 30);
    delay(200);
  }
  
  if (state > 0) {
    if (Pwm > 40 && millis() - time > 600000UL) { // 10分後
      Pwm = 40;
      analogWrite(MOTOR_PIN, Pwm); // めいっぱい遅く
      beep(SPEAKER_PIN, 262, 20); 

    } else if (Pwm > 120 && millis() - time > 120000UL) { // 2分後
      Pwm = 120;
      analogWrite(MOTOR_PIN, Pwm); // まあまあ遅く
      beep(SPEAKER_PIN, 392, 20); 
    }
  }
  
  if (state > 0 && digitalRead(START_SW) == LOW) {
    
    
    state--;
    if (state == 0) {
      Pwm = 0;
      analogWrite(MOTOR_PIN, Pwm);
      beep(SPEAKER_PIN, 440, 30);
      delay(30);
      beep(SPEAKER_PIN, 440, 30);
      
    } else {
      
      switch (state) {
        case 4:
          Pwm = 180;
          analogWrite(MOTOR_PIN, Pwm);
          beep(SPEAKER_PIN, 783, 30);
          break;
        case 3:
          Pwm = 120;
          analogWrite(MOTOR_PIN, Pwm);
          beep(SPEAKER_PIN, 700, 30);
          break;
        case 2:
          Pwm = 70;
          analogWrite(MOTOR_PIN, Pwm);
          beep(SPEAKER_PIN, 660, 30);
          break;
        case 1:
          Pwm = 40;
          analogWrite(MOTOR_PIN, Pwm);
          beep(SPEAKER_PIN, 587, 30);
          break;
      }
      
    }
    
    delay(200);
  } 
  
  if (state > 0 && millis() - time > 2400000UL) { // 40分後
    Pwm = 0;
    analogWrite(MOTOR_PIN, Pwm); // stop
    state = 0;
    
    beep(SPEAKER_PIN, 523, 50);
    delay(100);
    beep(SPEAKER_PIN, 523, 50);
    delay(100);
    beep(SPEAKER_PIN, 523, 50);
    delay(100);
    beep(SPEAKER_PIN, 523, 50);
    
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
