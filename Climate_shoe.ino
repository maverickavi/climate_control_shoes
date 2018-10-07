const int cycles = 500, pwmPins[2] = {3, 5}, pins[2] = {2, 4}, targetTemperature = 22, c = 50;
float m;
void setup() {
  Serial.begin(9600);
  for (int i = 2; i < 6; i++) pinMode(i, OUTPUT);
  float initialTemperature = 0;
  for (int i = 0; i < cycles; i++) initialTemperature += analogRead(7) * 125 / 256;
  initialTemperature /= cycles;
  //while (Serial.available()==0);
  //targetTemperature = Serial.read()-'0';
  //if (targetTemperature < 21) targetTemperature = 21;
  m = 255 / sqrt(sq(initialTemperature - targetTemperature));
}

void loop() {
  Serial.println();
  float temperature = 0;       
  for (int i = 0; i < cycles; i++) temperature += analogRead(7) * 125 / 256;
  temperature /= cycles;
  Serial.print(int(temperature));
  Serial.print("\t");
  float difference = temperature - targetTemperature;
  int Y = int(m * sqrt(sq(difference))) + c;
  if (Y > 255) Y = 255;
  Serial.print(Y); 
  digitalWrite(pins[0], difference >= 0);
  digitalWrite(pins[1], difference < 0);
  digitalWrite(pwmPins[difference >= 0], 0);
  analogWrite(pwmPins[difference < 0], Y);
}

