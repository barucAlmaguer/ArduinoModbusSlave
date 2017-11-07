#define JOY_SW      A2
#define JOY_X       A1
#define JOY_Y       A0
#define MODBUS_RT   2
#define MODBUS_PORT Serial1

void setup() {
  // put your setup code here, to run once:
  MODBUS_PORT.begin(9600);
  Serial.begin(9600);
  pinMode(JOY_SW,     INPUT);
  pinMode(JOY_X,      INPUT);
  pinMode(JOY_Y,      INPUT);
  pinMode(MODBUS_RT,  INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  while(MODBUS_PORT.available()){
    Serial.write(MODBUS_PORT.read());
  }
  Serial.print("X=");
  Serial.print(analogRead(JOY_X));
  Serial.print("  Y=");
  Serial.print(analogRead(JOY_Y));
  Serial.print("  SW=");
  Serial.println(digitalRead(JOY_SW) == LOW ? "PUCH" : "OFF");
  delay(100);
}
