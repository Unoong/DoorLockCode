#define W0 P2_1
#define W1 P2_2
#define DoorP P1_6
#define DoorE P1_0

static unsigned long int cards[]={7142197,7142204,7142180,7142175,7142159,7142198,7142160,7142242,7142199,7142179,7142250,7142186,7142251,7142178,7142163,7142161,7142162,4652198,7142173,7142202,7142174,7142210,7142201,7142203,7142211,7142158,7142157,7142164,7142165,7142209,7142208,7142207,7142206,7142205,7142156,7142200,7142249,7142248,7142243,7142244,7142245,7142246,
  7142177,
  7142221,
7142223,
7142224,
7142225,
7142226,
7142227,
7142228,
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
};
char bits[80];
int bitcnt=0;
unsigned long long bitw=0;
unsigned int timeout=1000;
boolean valid = true;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
   
  pinMode(W0, INPUT_PULLUP); 
  pinMode(W1, INPUT_PULLUP); 
  pinMode(DoorP,OUTPUT);
  pinMode(DoorE,OUTPUT);
  digitalWrite(DoorP, LOW); 
  digitalWrite(DoorE, LOW); 
  
  
  attachInterrupt((W0), W0ISR, FALLING);
  attachInterrupt((W1), W1ISR, FALLING);
  Serial.println("Hello World!");
  
  for(int i=0; i<sizeof(bits); i++) bits[i]=0;
}


void loop()
{
  digitalWrite(DoorP, LOW);
  digitalWrite(DoorE, LOW);
  if (timeout>0) timeout--;
  if (timeout == 0 && bitcnt != 0){
    //Serial.print((long unsigned int)(bitw>>32),BIN);
    //Serial.print((long unsigned int)bitw,BIN);
      //  bitw = 0x122D9F628;
    for(int i=bitcnt; i!=0; i--) Serial.print((unsigned int)(bitw>>(i-1) & 0x00000001));
    Serial.print(" (");
    Serial.print(bitcnt);
    Serial.println(")");
    

    boolean ep,op;
    unsigned int      site;
    unsigned long int card;
    
    site = (bitw>>25) & 0x7f;
    card = (bitw>>1)  & 0xffffff;
    op = (bitw>>0)  & 0x1;
    ep = (bitw>>32) & 0x1;
    if (parity(site) != ep) valid=false;
    if (parity(card) == op) valid=false;
    Serial.print("Site: "); Serial.println(site);
    Serial.print("Card: "); Serial.println(card);
    Serial.print("ep: "); Serial.print(parity(site));Serial.println(ep);
    Serial.print("op: "); Serial.print(parity(card));Serial.println(op);
    Serial.print("Parity Check: ");Serial.println(valid?"Valid":"Error");
    if (valid){
      if (site==17)
        for (int i=0; i<sizeof(cards); i++)
          if (cards[i] == card){
            Serial.println("Match!");
            digitalWrite(DoorP, HIGH);
            delay(3000);
            goto done;
          }
    



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
  bitw = (bitw<<1) | 0x0;
  bitcnt++;
  timeout = 2000;
  
}

void W1ISR(){
  bitw = (bitw<<1) | 0x1;
  bitcnt++;
  timeout = 2000;
}

int parity(unsigned long int x) {
   unsigned long int y;
   y = x ^ (x >> 1);
   y = y ^ (y >> 2);
   y = y ^ (y >> 4);
   y = y ^ (y >> 8);
   y = y ^ (y >>16);
   return y & 1;
}
