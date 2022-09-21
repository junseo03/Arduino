#define PIN_LED 7
unsigned int count, toggle;
void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  while(!Serial) {
    ;
  }
  Serial.println("Hello World!");
  count = toggle = 0;
  digitalWrite(PIN_LED, toggle);
  
}

void loop(){
  delay(1000);
  for(int i=0; i<12;i++){
    toggle = i%2;
    digitalWrite(PIN_LED, toggle);
    delay(100);
  }
  while(1){

  }
}

int toggle_state(int toggle){
  return toggle;
}
