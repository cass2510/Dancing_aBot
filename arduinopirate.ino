#include <Servo.h>

Servo leftServo;   // 왼쪽 서보
Servo rightServo;  // 오른쪽 서보

const int leftPin = 12;   // 왼쪽 서보 핀
const int rightPin = 13;  // 오른쪽 서보 핀
const int buzzerPin = 9;  // 피에조 스피커 핀

// LED 핀 설정
const int ledPin1 = 2;    // 첫 번째 LED 핀
const int ledPin2 = 8;    // 두 번째 LED 핀
const int ledPin3 = 11;   // 세 번째 LED 핀

#define NOTE_C4  262    
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_B5  988

const float songspeed = 1.6; // 노래 속도 조절

int notes[] = {
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,

   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,

   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,

   NOTE_A4, NOTE_A4, 
   //Repeat of first part
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,

   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,

   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,

   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,
   //End of Repeat

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4
};

int duration[] = {        
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125,

  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125,

  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,

  250, 125,
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125,

  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125,

  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,


  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500,

  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500
};

unsigned long lastMoveTime = 0; // 마지막 움직임 시간
unsigned long lastLEDBlinkTime = 0; // 마지막 LED 깜빡임 시간
const unsigned long moveInterval = 2000; // 이동 간격 (2초)
const unsigned long ledBlinkInterval = 1000; // LED 깜빡임 간격 (1초)

int currentNote = 0; // 현재 재생 중인 음표 인덱스
unsigned long noteStartTime = 0; // 현재 음표 시작 시간

void setup() {
  leftServo.attach(leftPin);   // 왼쪽 서보 핀 연결
  rightServo.attach(rightPin);  // 오른쪽 서보 핀 연결
  pinMode(buzzerPin, OUTPUT);
  
  // LED 핀 모드 설정
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  
  randomSeed(analogRead(0)); // 랜덤 시드 초기화
}

void loop() {
  unsigned long currentMillis = millis();

  // LED 깜빡임 처리
  if (currentMillis - lastLEDBlinkTime >= ledBlinkInterval) {
    toggleLEDs();
    lastLEDBlinkTime = currentMillis;
  }

  // 랜덤으로 움직임
  if (currentMillis - lastMoveTime >= moveInterval) {
    randomMove();
    lastMoveTime = currentMillis;
  }

  playMelody();
}

void playMelody() {
  unsigned long currentMillis = millis();
  if (currentMillis - noteStartTime >= duration[currentNote] * songspeed) {
    noTone(buzzerPin);
    currentNote++;
    if (currentNote >= sizeof(notes) / sizeof(notes[0])) {
      currentNote = 0; // 노래가 끝나면 처음부터 다시 시작
    }
    tone(buzzerPin, notes[currentNote], duration[currentNote] * songspeed);
    noteStartTime = currentMillis;
  }
}

void toggleLEDs() {
  digitalWrite(ledPin1, !digitalRead(ledPin1));
  digitalWrite(ledPin2, !digitalRead(ledPin2));
  digitalWrite(ledPin3, !digitalRead(ledPin3));
}
void moveForward() {
  leftServo.write(180); // 왼쪽 바퀴 전진
  rightServo.write(0);  // 오른쪽 바퀴 전진
}

void moveBackward() {
  leftServo.write(0);   // 왼쪽 바퀴 후진
  rightServo.write(180); // 오른쪽 바퀴 후진
}

void turnLeft() {
  leftServo.write(90);  // 왼쪽 바퀴 정지
  rightServo.write(0);  // 오른쪽 바퀴 전진
}

void turnRight() {
  leftServo.write(0);   // 왼쪽 바퀴 전진
  rightServo.write(90); // 오른쪽 바퀴 정지
}

void stopMovement() {
  leftServo.write(90);  // 왼쪽 바퀴 정지
  rightServo.write(90); // 오른쪽 바퀴 정지
}

void randomMove() {
  int direction = random(5); // 0: 정지, 1: 앞으로, 2: 뒤로, 3: 좌회전, 4: 우회전
  switch (direction) {
    case 0: stopMovement(); break;
    case 1: moveForward(); break;
    case 2: moveBackward(); break;
    case 3: turnLeft(); break;
    case 4: turnRight(); break;
  }
  
}