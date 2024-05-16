#define Button 5
#define ENA 2
#define ENB 3 
#define PWM 10 

volatile long EncoderValue = 0 ;


int interval = 1000;
long lastMillis = 0 ;
long currentMillis = 0 ;



int rpm = 0 ;
bool rpmCalculation = false;
int motorPwm = 0 ;

void setup() {
  Serial.begin(9600);

  pinMode(Button,INPUT_PULLUP);
  pinMode(ENA,INPUT_PULLUP);
  pinMode(ENB,INPUT);

  attachInterrupt(digitalPinToInterrupt(ENA),updateEncoder,RISING);
  Serial.println("Press the button to start");
}

void loop() {
  if (digitalRead(Button) == LOW){
    rpmCalculation = !rpmCalculation;
    if(rpmCalculation == true){
      Serial.println("Starting");
      Serial.println("PWM\tRPM");
    }else if (rpmCalculation == false){
      Serial.println("Stoping");
    }
    delay(500);
    EncoderValue= 0 ;
    lastMillis = millis();
  }
  currentMillis = millis();
  if(currentMillis - lastMillis > interval){
    lastMillis = currentMillis;

    if(rpmCalculation == true && motorPwm < 250){
      motorPwm += 50;
      analogWrite(PWM ,motorPwm);
    }else if (rpmCalculation == false && motorPwm > 0){
      motorPwm -= 50;
      analogWrite(PWM , motorPwm);
    }
  }

  rpm= (float)(EncoderValue * 60 / 100);

  if(motorPwm > 0 || rpm > 0) {
    Serial.print(motorPwm);
    Serial.print('\t');
    Serial.print(rpm);
    
  }
  EncoderValue=0;
}
void updateEncoder(){
  EncoderValue++;
  }
