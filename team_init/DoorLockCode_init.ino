#include <Time.h>
#include <TimeLib.h>
#include <Keypad.h>  // Keypad.h 라이브러리를 호출
int i=0;
int password = 0;
char secretCode[7];  // 비밀번호 설정
int position = 0; 
int wrong = 0;   //틀리 회수
int ft=10,lt=20;  // 제한할 시간
<<<<<<< HEAD
int key_security = 1234567;
=======
int key = 1234567 ;
>>>>>>> fe03cf62358545f0708440c04c203c2962d5c7c3
int password_origin = 0;
int bitw=0;
// 비밀번호 비교시 쓸 변수 선언(맞는 경우와 틀린경우 2가지)

boolean valid = true;
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
int DoorE = 6 ;
// LED 2개의 핀번호 설정

void setup(){
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(DoorE,OUTPUT); 
  digitalWrite(DoorE, LOW); 
  setLocked(true);
  Serial.begin(9600);
    
  setTime(23,59,0,26,11,16);  //현재 시간으로 세팅
 }


void loop(){
<<<<<<< HEAD
  int insert = matchpassword(password_origin,&key_security);
//  char key = keypad.getKey(); // 키패드에서 입력된 값을 가져옵니다.

  if(hour()>=ft && hour()<lt) {      //현재 시간이 제한된 시간안에 속하면 
       blink();                      //빨간 불이나고 입력 받지 않음.
  }
  else{
=======
    boolean ep,op;      
    unsigned int      site;
    unsigned long int card; //4byte 범위
  
  
>>>>>>> fe03cf62358545f0708440c04c203c2962d5c7c3
  if((key >= '0' && key <= '9') || (key >= 'A' && key <='D')
    || (key == '*' || key == '#'))
    {
  // 키패드에서 입력된 값을 확인, 맞게 입력된 값일 경우(키패드에 있는 버튼이 맞을경우) 비교
      if(key == '*')
      { // * 버튼을 눌렀을 경우 초기화
      position = 0; 
      wrong = 0; 
      setLocked(true); // 잠금상태로 세팅
    } 
      else if (key == '+')
 {    
      int ft = atoi(keypad.getKey());
      int lt = atoi(keypad.getKey());
  
 if (ft>lt) 
 {    if(hour()>=ft || hour()<=lt)
      {blink();
      setLocked(true);}
      else setLocked(false);
  } 
 else if (hour()>=ft && hour()<lt) {      //현재 시간이 제한된 시간안에 속하면 
       blink(); // R LED 를 켜주고 
       setLocked(true) ;  }  // Lock 해줌
      
      else setLocked(false);
   
 
  }   // + 일때 함수 구현

    


   else{
    
    for(i=0; i<7 ; i++)
  { secretCode[i] = keypad.getKey(); } // 비밀번호를 만들어 저장

//  키를 encrypt 하는 프로그램 작성


     if(key == secretCode[position])
    { // 해당 자리에 맞는 비밀번호가 입력됬을 경우
      position++; // 다음 자리로 넘어 감
      wrong = 0; // 비밀번호 오류 값을 0으로 만듬
    }
    
    else if(key != secretCode[position])
    { // 해당 자리에 맞지 않는 비밀번호가 입력됬을 경우
      position = 0; // 비밀번호를 맞았을 경우를 0으로 만듬
    
      wrong++; // 비밀번호 오류 값을 늘려준다
   }
  
    if(position == 4){ // 4자리 비밀번호가 모두 맞았을 경우
      setLocked(false); // 잠금상태를 해제 함
      digitalWrite(DoorE, HIGH);  // 문이 열림
    }
    
    if(wrong == 4){ // 비밀번호 오류를 4번 했을 경우
      blink(); // Red LED를 깜빡여 준다.
   
    }

bitw = atoi(secretCode);
 site = (bitw>>25) & 0x7f;   // 25bit 오른쪽으로 옮겨 01111111 과 비트연산 => 왜 하는지 모르겠음
    card = (bitw>>1)  & 0xffffff;   //1111111111111111
    op = (bitw>>0)  & 0x1;    // xxxx xxxx xxxx & 0001
    ep = (bitw>>32) & 0x1;    // False
    if (parity(site) != ep) valid=false;      
    if (parity(card) == op) valid=false;      
  
  }
   
  }
  
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

void blink(){ // Red LED를 깜빡여 주는 함수 , 4번 오류 또는 제한시간에 사용되면 도어락이 잠기는 신호로 사용됨
  for(int i = 0; i < 8; i++){ // 딜레이 만큼 Red LED를 껐다 켰다 해줌. 총 8회
    digitalWrite(redPin, LOW);
    delay(500);
    digitalWrite(redPin, HIGH);
    delay(500);
  }
}

<<<<<<< HEAD
int makepassword(int *password,int *key)  //비밀번호를 입력받는 함수
{
  int i;                                  //자리수를 표현하는 변수
  char input[7];                          //입력받은 문자열
  for(i=0;i<7;i++) {                      //for문으로 7자리의 input문자열을 채운다.
   input[i] = keypad.getKey(); 
  }
  password = atoi(input) ^ key;     //xor연산을 통해서 비밀번호를 만들어낸다.
  return 1;
 }

int matchpassword(int *password, int *key)  //비밀번호를 확인하는 함수
{
  char input[8];                           //비밀번호를 입력받는 변수
  int i;                            
  for(i=0;i<8;i++) {                       //비밀번호를 입력받는다.
   input[i] = keypad.getKey(); 
  }
  if(password == atoi(input)^key) { //해당 input값이 비밀번호와 같은지 검사한다.
    return 1;
  }
  else {
    return 0;                             //비밀번호가 맞으면 1 , 틀리면 0 을 리턴한다.
  }
}
=======
void encrypted()
{}

>>>>>>> fe03cf62358545f0708440c04c203c2962d5c7c3

int parity(unsigned long int x)
{    unsigned long int y;
   y = x ^ (x >> 1);  // ^ : bit XOR  
   y = y ^ (y >> 2);    
   y = y ^ (y >> 4);
   y = y ^ (y >> 8);
   y = y ^ (y >>16);
   return y & 1;    // & : bit AND
  }  
