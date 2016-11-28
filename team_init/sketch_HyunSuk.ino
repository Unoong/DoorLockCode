#include <Keypad.h>  // Keypad.h 라이브러리를 호출
#include <Time.h>

char* secretCode = "5678";  // 비밀번호 설정
int position = 0; 
int wrong = 0;
char key = "teaminit";
int password_origin = 0;
// 비밀번호 비교시 쓸 변수 선언(맞는 경우와 틀린경우 2가지)

const byte rows = 4;
const byte cols = 4;
// 키패드의 행, 열의 갯수

char keys[rows][cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
// 키패드 버튼 위치 설정

byte rowPins[rows] = {8, 7, 6, 5};
byte colPins[cols] = {4, 3, 2, 1};
// 키패드에 연결된 핀번호 설정(데이터 시트 참고)

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);
// 키패드 오브젝트 생성

int redPin = 13;
int greenPin = 12;
// LED 2개의 핀번호 설정

void setup(){
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  setLocked(true);
  makepassword(&password_origin,key); 
}
// 2개의 LED를 세팅해주고, 잠금상태를 기본으로 세팅해 줍니다.


void loop(){
  int insert = matchpassword(password_origin,key);
//  char key = keypad.getKey(); // 키패드에서 입력된 값을 가져옵니다.
  
  if((key >= '0' && key <= '9') || (key >= 'A' && key <='D')
    || (key == '*' || key == '#')){
  // 키패드에서 입력된 값을 조사하여 맞게 입력된 값일 경우(키패드에 있는 버튼이 맞을경우) 비교

    if(key == '*' || key == '#'){ // *, # 버튼을 눌렀을 경우
      position = 0; 
      wrong = 0; // 입력 초기화
      setLocked(true); // 잠금상태로 세팅
    } 
 
    else if(key == secretCode[position]){ // 해당 자리에 맞는 비밀번호가 입력됬을 경우
      position++; // 다음 자리로 넘어 감
      wrong = 0; // 비밀번호 오류 값을 0으로 만듬
    }
    
    else if(key != secretCode[position]){ // 해당 자리에 맞지 않는 비밀번호가 입력됬을 경우
      position = 0; // 비밀번호를 맞았을 경우를 0으로 만듬
      setLocked(true); // 잠금상태로 세팅
      wrong++; // 비밀번호 오류 값을 늘려준다
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

int makepassword(int *password,char key) 
{
  int i;
  char input[8];
  for(i=0;i<8;i++) {
   input[i] = keypad.getKey(); 
  }
  password = atoi(input) ^ atoi(key);
  return 1;
  }

int matchpassword(int password, char key) {
  char input[8];
  int i;
  for(i=0;i<8;i++) {
   input[i] = keypad.getKey(); 
  }
  if(password == atoi(input)^atoi(key)) {
    return 1;
  }
  else {
    return 0;
  }
}

