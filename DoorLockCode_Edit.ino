
#define W0 3
#define W1 4
#define DoorP 5
#define DoorE 6

// 가능한 비밀번호 풀
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
char bits[80] = 0;
int bitcnt = 0;
unsigned long long bitw = 0;  // unsigned long long ==> 8byte(64bit) 범위
unsigned int timeout = 1000;  
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
  
  
  attachInterrupt((W0), W0ISR, FALLING);  //   W0 단자 (여기서는 3번) 에서 입력값이 High 에서 Low 로 바뀔때  인터럽트(W0ISR) 발생시킴
                                          // 문법: attachInterrut(unit8_t pin, void(*function)(void), int mode)
  attachInterrupt((W1), W1ISR, FALLING);
  Serial.println("Hello World!");       
  


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
    
    site = (bitw>>25) & 0x7f;   // 25bit 오른쪽으로 옮겨 01111111 과 비트연산 => 왜 하는지 모르겠음
    card = (bitw>>1)  & 0xffffff;   //1111111111111111
    op = (bitw>>0)  & 0x1;    // xxxx xxxx xxxx & 0001
    ep = (bitw>>32) & 0x1;    //  Parity check 를 위해서 op & ep 값 설정
    if (parity(site) != ep) valid=false;      // 
    if (parity(card) == op) valid=false;      // 
    Serial.print("Site: "); Serial.println(site);   //doorlock site 값 출력
    Serial.print("Card: "); Serial.println(card);  // doorlock card 값 출력
    Serial.print("ep: "); Serial.print(parity(site));Serial.println(ep);  // doorlock ep 값 출력
    Serial.print("op: "); Serial.print(parity(card));Serial.println(op);  // doorlock op 값 출력
    Serial.print("Parity Check: ");Serial.println(valid?"Valid":"Error");
    if (valid){
      if (site==17)  // 10001(2)
        for (int i=0; i<sizeof(cards); i++)
          if (cards[i] == card){
            Serial.println("Match!");
            digitalWrite(DoorP, HIGH);
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

void W0ISR(){
  bitw = (bitw<<1) | 0x0; // bitw 를 왼쪽으로 1 bit shift 된 값과 OR 연산 수행 
  bitcnt++;               // bit count 증가시킴
  timeout = 2000;         //
  
}

void W1ISR(){
  bitw = (bitw<<1) | 0x1;
  bitcnt++;
  timeout = 2000;
}


//parity bit , 데이터가 잘 전송이 됬는지 알아보는 역할;;  bit 연산은 8bit 단위로 수행됨 연산을 하면 밀려나가는 부분은 모두 0 처리
int parity(unsigned long int x) {
    unsigned long int y;
   y = x ^ (x >> 1);  // ^ : bit XOR  
   y = y ^ (y >> 2);    
   y = y ^ (y >> 4);
   y = y ^ (y >> 8);
   y = y ^ (y >>16);
   return y & 1;    // & : bit AND
}  
