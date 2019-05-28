int LEDPIN=D6;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
analogWrite(LEDPIN,1023);
}

void loop() {
  // put your main code here, to run repeatedly:
  int dutycycle=analogRead(A0);
  if(dutycycle > 1023) dutycycle=1023;
  Serial.print("Duty Cycle:");
  Serial.println(dutycycle);
  analogWrite(LEDPIN,dutycycle);
  delay(1000);

}
