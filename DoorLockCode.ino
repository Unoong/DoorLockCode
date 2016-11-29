#define W0 3        //입력 단자 설정
#define W1 4
#define DoorP 5
#define DoorE 6

/* 기본적인 코드 원리 
 *  Wiegand 프로토콜을 구현하기 위한 rfid 리더기와 자기선 리더기에 사용되는 코드이다.
 *  wiegand format이란 출입통제 시스템에 주로 사용되는 접근식 RF카드리더에 대부분 적용되는 인터페이스를 말한다.
 *  Wiegand 프로토콜은 even parity bit, facility code, card number, odd parity bit 로 구성된다. 
 *  이 코드에서는 33bit의 데이터를 패리티 검사한다.
*/

// 저장되어 있는 고유 card 정보들.  (card number)
static unsigned long int cards[]=
{7142197,7142204,7142180,7142175,7142159,7142198,7142160,7142242,7142199,7142179,7142250,7142186,7142251,7142178,7142163,7142161,7142162,4652198,7142173,7142202,7142174,7142210,7142201,7142203,7142211,7142158,7142157,7142164,7142165,7142209,7142208,7142207,7142206,7142205,7142156,7142200,7142249,7142248,7142243,7142244,7142245,7142246,
  7142177,
  7142221,
  7142223,
  7142224,
  7142225,
  7142226,
  7142227,


  7142229, 
  7142230,
  7142231,
  7744836,
  7744835,
  7744834,
  7142236,
  7142237,
  7142238,
  7142239,
  7142240,
  7142241,
  7142252
                };  // 변수를 static 으로 정의하여 유효범위를 넘어가지 않아도 소멸하지 않도록 함 
char bits[80];
int bitcnt=0;         // bitcnt 초기화
unsigned long long bitw=0;  // unsigned long long ==> 8byte(64bit) 범위
unsigned int timeout=1000;  
boolean valid = true;  //boolean 으로 True/False 판정 doorlock 

void setup()  // 보드의 단자에 대하서 input output 정의 및 시리얼 모니터 사용 결정
{
  // put your setup code here, to run once:
  Serial.begin(9600);   //시리얼 통신 시작 9600 bit/s
   
  pinMode(W0, INPUT_PULLUP); 
  pinMode(W1, INPUT_PULLUP); 
  pinMode(DoorP,OUTPUT);
  pinMode(DoorE,OUTPUT);
  digitalWrite(DoorP, LOW); 
  digitalWrite(DoorE, LOW); 
  
  // '1'과 '0'을 나타내는 2개의 wire를 통해 1과 0 bit를 읽는 pulse를 출력한다.
  // pulse를 세는 것이 필요하다.

  attachInterrupt((W0), W0ISR, FALLING);  //   W0 단자 (여기서는 3번) 에서 입력값이 High 에서 Low 로 바뀔때  인터럽트(W0ISR) 발생시킴
                                          // 문법: attachInterrut(unit8_t pin, void(*function)(void), int mode)
  attachInterrupt((W1), W1ISR, FALLING);  //  마찬가지로 W1 단자에서 인터럽트 발생.
  Serial.println("Hello World!");       
  
  for(int i=0; i<sizeof(bits); i++) bits[i]=0;
}


void loop()
{
  digitalWrite(DoorP, LOW);
  digitalWrite(DoorE, LOW);
  if (timeout>0) timeout--;         // timeout 이 0이 될때 까지  잠깐 시간을 둔다., 적어도 한번의 인터럽트가 발생해야 비밀번호 확인과정을 거치게 되어있음  
  if (timeout == 0 && bitcnt != 0){
    //Serial.print((long unsigned int)(bitw>>32),BIN);
    //Serial.print((long unsigned int)bitw,BIN);
      //  bitw = 0x122D9F628;=>36bit
    for(int i=bitcnt; i!=0; i--) Serial.print((unsigned int)(bitw>>(i-1) & 0x00000001)); // 오른쪽 shift , 특정 비트 클리어 ,,, 인터럽트가 발생한 숫자만큼 비트를 하나씩 내리면서 1 이 있는 bitw 를 확인
    Serial.print(" (");
    Serial.print(bitcnt);  //bitcnt 값을 serial 통신에 출력 
    Serial.println(")");



    

    boolean ep,op;      
     unsigned int      site;
    unsigned long int card; //4byte 범위
    
    site = (bitw>>25) & 0x7f;   // bitw의 앞 7비트 (site) 값을 추출 하는 과정. ( bitw를 오른쪽으로 25bit 쉬프트 시킨 후 01111111과 AND 연산을 수행)
    card = (bitw>>1)  & 0xffffff;   //bitw의 site 비트 뒤의 24비트 (card) 값을 추출 하는 과정. ( bitw를 오른쪽으로 1bit 쉬프트 시킨후 0xffffff와 AND 연산을 수행)
    op = (bitw>>0)  & 0x1;    // bitw의 odd parity bit 를 추출 하는 과정
    ep = (bitw>>32) & 0x1;    // bitw의 even parity bit 를 추출 하는 과정


    //패리티 검사
    if (parity(site) != ep) valid=false;      // site 값의 패리티 검사에서 오류가 생기면 ( 짝수 패리티 검사) vaild 에 false를 넣는다.
    if (parity(card) == op) valid=false;      // card 값의 패리티 검사에서 오류가 생기면 ( 홀수 패리티 검사) vaild 에 false를 넣는다.
    Serial.print("Site: "); Serial.println(site);   //doorlock site 값 출력
    Serial.print("Card: "); Serial.println(card);  // doorlock card 값 출력
    Serial.print("ep: "); Serial.print(parity(site));Serial.println(ep);  // doorlock ep 값 출력
    Serial.print("op: "); Serial.print(parity(card));Serial.println(op);  // doorlock op 값 출력
    Serial.print("Parity Check: ");Serial.println(valid?"Valid":"Error");
    if (valid){
      if (site==17)  // 10001(2)
        for (int i=0; i<sizeof(cards); i++)
          if (cards[i] == card){                  // 비밀번호 풀 과 card 값을 비교한다.
            Serial.println("Match!");            // 같다면 Match 출력하고
            digitalWrite(DoorP, HIGH);            // DoorLock 이 열린다.
            delay(3000);
            goto done;
          }   //만약 비밀번호가 그 안에 있다면 DoorP 에 해당하는 단자에 전류가 흘러 열림, 3초 딜레이 후 다시 수행..
    



   Serial.println("Error!");
   digitalWrite(DoorE, HIGH);
   delay(3000);
    }
 
   done:
   bitcnt=0;
   bitw = 0;
   valid = true;
  }

}

void W0ISR(){  // W0단자에 인터럽트가 들어왔을 경우.
  bitw = (bitw<<1) | 0x0; // bitw 를 왼쪽으로 1 bit shift 시키고 0과 OR 연산 수행 --> bitw값 LSB에 0을 추가시킨다.
  bitcnt++;               // bit count 증가시킴
  timeout = 2000;         // timeout 을 초기화 시킨다.
  
}

void W1ISR(){   // W1단자에 인터럽트가 들어왔을 경우
  bitw = (bitw<<1) | 0x1;  // bitw 를 왼쪽으로 1 bit shift 시키고 1과 XOR 연산 수행 -->bitw값 LSB에 1을 추가시킨다.
  bitcnt++;                //bit count 값 증가
  timeout = 2000;          //timeout을 초기화 시킨다.
}


//parity bit 정의, 데이터가 잘 전송이 됬는지 알아보는 역할을 함  ;; it 연산은 8bit 단위로 수행됨 연산을 하면 밀려나가는 부분은 모두 0 처리
int parity(unsigned long int x) {    // 검사할 비트 값을 1,2,4,8,16 비트씩 오른쪽으로 쉬프트 시키며 그 한 단계 전 비트와 XOR 연산을 수행한다.
    unsigned long int y;
   y = x ^ (x >> 1);  // ^ : bit XOR  
   y = y ^ (y >> 2);    
   y = y ^ (y >> 4);
   y = y ^ (y >> 8);
   y = y ^ (y >>16);
   return y & 1;    // & : bit AND
}  
