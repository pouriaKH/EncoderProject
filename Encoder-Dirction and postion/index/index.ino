#define ENA 2
#define ENB 3
volatile int pos = 0 ;
bool CCW ;
void setup(){
  pinMode(ENA,INPUT);
  pinMode(ENA,INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(ENA),UptadeEncoder,RISING);
}
void loop(){
  Serial.print("pos:");
  Serial.println(pos);
  Serial.print("CCW || CW:");
  if (CCW) Serial.println("CCW");
  else Serial.println("CW");
  delay(20);
}
void UptadeEncoder(){
  int a = digitalRead(ENB);
  if(a > 0){
    CCW = true; // moves counter clock wise (may change on pin)
    pos++;
  }
  else {
    CCW = false; // moves clock wise (may change on pin)
    pos--;
  }
}