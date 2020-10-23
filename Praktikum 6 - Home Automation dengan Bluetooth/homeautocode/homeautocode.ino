String voice;
int pinLampuRuang = 6; // Lamp
int pinKipas = 5;      // Motor DC
int pinLampuTidur = 4; // LED

void setup() {
Serial.begin(9600);
pinMode(pinLampuRuang, OUTPUT);
pinMode(pinKipas, OUTPUT);
pinMode(pinLampuTidur, OUTPUT);
}

void loop() {
while(Serial.available()){
  delay(3);
  char c = Serial.read();
  voice+=c;}

if(voice.length() >0){
  Serial.println(voice);
  if(voice == "light on")
  {digitalWrite(pinLampuRuang, HIGH);}
  else if(voice == "light off")
  {digitalWrite(pinLampuRuang, LOW);}
  else if(voice == "fan on")
  {digitalWrite(pinKipas, HIGH);}
  else if(voice == "fan off")
  {digitalWrite(pinKipas, LOW);}
  else if(voice == "night lamp on")
  {digitalWrite(pinLampuTidur, HIGH);}
  else if(voice == "night lamp off")
  {digitalWrite(pinLampuTidur, LOW);}
  else if(voice == "all on")
  {digitalWrite(pinLampuTidur, HIGH);
    digitalWrite(pinKipas, HIGH);
  digitalWrite(pinLampuRuang, HIGH);}
  else if(voice == "all off")
  {digitalWrite(pinLampuTidur, LOW);
    digitalWrite(pinKipas, LOW);
  digitalWrite(pinLampuRuang, LOW);}
  voice = "";}
}
