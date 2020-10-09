
int ml = A0; // motor DC dihubungkan ke pin analog A0 arduiono
int h = 255; // 5 volt
int l = 0;   // 0 volt
String motion;

void setup() {

  Serial.begin(9600);
  pinMode(ml, OUTPUT);
  analogWrite(ml, h); // motor dalam Kondisi Diam
  
}

void loop() {

  Serial.println("Silahkan ketik 'p' untuk memutar, 's' untuk berhenti");
  
  while (Serial.available() == 0) { 

    motion = Serial.readString();

    if (motion == "p") {
      analogWrite(ml, l);   
    }

    if (motion == "s") {
      analogWrite(ml, h);   
    }
  }
}
