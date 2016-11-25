#include <Keypad.h>  // Keypad.h 라이브러리 호출

const byte rows = 4;
const byte cols = 4;
// 키패드의 행, 열의 갯수

int position = 0; // strcmp 함수가 arduino 에서는 없어서 비밀번호 비교 할때 필요한 변수 선언
int trial = 0;
int Password_Length=0;
int i=0;
// 비밀번호 비교시 쓸 변수 선언(맞는 경우와 틀린경우 2가지)


char keys[rows][cols] = 
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
// 키패드 버튼 4*4 행렬로 표현

byte rowPins[rows] = {8, 7, 6, 5};
byte colPins[cols] = {4, 3, 2, 1};
// 키패드에 연결된 핀번호 설정 ( keypad.h 를 보면 기본설정으로 되어있음 )

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);
//  (keypad ::Keypad(char *userKeymap, byte *row, byte *col, byte numRows, byte numCols))

int redPin = 13;
int greenPin = 12;
// LED 2개의 핀번호 설정

void setup(){
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  setLocked(true); // 초기 세팅 잠금상태로, boolean<->integer
}



void loop(){
  
  char *Length = keypad.getKey(); // 초기 암호 설정, 키패드에서 입력된 값을 가져옮, keypad.h 라이브러리 의 keypad.getKey 함수
  int Password_Length = atoi(*Length);

  for(i=0; i<Password_Length; i++) 
  {
  char password[i] = keypad.getKey(); // 
  }
    if(key == '*' || key == '#'){ // *, # 버튼을 눌렀을 경우 입력 초기화를 시킴
      position = 0; 
      trial = 0; 
      setLocked(true); // 잠금상태로 세팅
    
 
    else if(key == Password[position])
    { // 해당 자리에 맞는 비밀번호가 입력됬을 경우
      position++; // 다음 자리로 넘어 감
      trial = 0; // 비밀번호 시도 값을 0으로 만듬
    }
    
    else if(key != Password[position]){ // 해당 자리에 맞지 않는 비밀번호가 입력됬을 경우
      position = 0; // 비밀번호를 맞았을 경우를 0으로 만듬
      setLocked(true); // 잠금상태로 세팅
      trial++; // 비밀번호 오류 값을 늘려준다
    }
  
    if(position == 4){ // 4자리 비밀번호가 모두 맞았을 경우
      setLocked(false); // 잠금상태를 해제 함
    }
    
    if(wrong == 4){ // 비밀번호 오류를 4번 했을 경우
      blink(); // Red LED를 깜빡여 준다.
      wrong = 0; // 비밀번호 오류 값을 0으로 만들어 준다.
    }
  }
  delay(100);
}

void setLocked(int locked){ // 잠금시와 해제시에 맞는 LED를 세팅해 주는 함수
  if(locked) { // 잠금시 Red LED를 켜주고, Green LED를 꺼준다.
  digitalWrite(redPin, HIGH);
  digitalWrite(greenPin, LOW); 
  }

  else{ // 해제시 Red LED를 꺼주고, Green LED를 켜준다.
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
  } 
}

void blink(){ // 비밀번호 4번 오류시 Red LED를 깜빡여 주는 함수.
  for(int i = 0; i < 8; i++){ // 딜레이 만큼 Red LED를 껐다 켰다 해준다. 총 8회
    digitalWrite(redPin, LOW);
    delay(500);
    digitalWrite(redPin, HIGH);
    delay(500);
  }
}

