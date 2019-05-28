int switchPin=D3;
int LedPin=D0;
int switchValue,switchValue1;
int switchPin1=D4;
int LedPin1=D1;

void setup() {
  // put your setup code here, to run once:
  pinMode(LedPin,OUTPUT);
   pinMode(switchPin,INPUT_PULLUP);
   pinMode(LedPin1,OUTPUT);
   pinMode(switchPin1,INPUT_PULLUP);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  switchValue = digitalRead(switchPin);
  digitalWrite(LedPin,!switchValue);
switchValue1 = digitalRead(switchPin1);
  digitalWrite(LedPin1,!switchValue1);

}
