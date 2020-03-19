void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long runMillis= millis();
  unsigned long allSeconds=millis()/1000;
  int runHours= (allSeconds/3600);
  int secsRemaining=allSeconds%3600;
  int runMinutes=secsRemaining/60;
  int runSeconds=secsRemaining%60;

  char buf[21];
  sprintf(buf,"%02d:%02d:%02d",runHours,runMinutes,runSeconds);
  Serial.println(buf);
  delay(1000);
}
