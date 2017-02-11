void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  Particle.process();
  digitalWrite(9, HIGH);
  delay(200);
  Particle.process();
  delay(200);
  digitalWrite(9, LOW); 
  delay(200);
  Particle.process();
  delay(200);
  Particle.process();
  delay(200);
  Particle.process();
  delay(200);
  Particle.process();
  delay(200);
  Particle.process();
  delay(200);
}
