char BYTE;

void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  digitalWrite(13,LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0) {
    BYTE=Serial.read();

    if(BYTE== '1'){
      digitalWrite(13,HIGH);
      Serial.write('a');
    } 
    if(BYTE == '0') {
      digitalWrite(13,LOW);
      Serial.write('b');
      
    }
    



    
  }

}
