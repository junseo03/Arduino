#include <Servo.h>

// Arduino pin assignment

#define PIN_POTENTIOMETER 3 // Potentiometer at Pin A3
#define PIN_IRsenser 0// Add IR Sensor Definition Here !!!
#define PIN_SERVO 10
#define PIN_LED 9

#define _DUTY_MIN 553  // servo full clock-wise position (0 degree)
#define _DUTY_NEU 1476 // servo neutral position (90 degree)
#define _DUTY_MAX 2399 // servo full counter-clockwise position (180 degree)
#define _DIST_MAX 500
#define _DIST_MIN 50
#define alpha 0.8

#define LOOP_INTERVAL 50   // Loop Interval (unit: msec)
#define INTERVAL 20
Servo myservo;
unsigned long last_loop_time;   // unit: msec

void setup()
{
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(57600);
}

void loop()
{
  unsigned long time_curr = millis();
  
  int a_value, duty;
  float ema;
  float dist_raw;
  float dist_prev;

  // wait until next event time
  if (time_curr < (last_loop_time + LOOP_INTERVAL))
    return;
  last_loop_time += LOOP_INTERVAL;
   
  // Remove Next line !!!
  a_value = analogRead(PIN_IRsenser);   // Read IR Sensor value !!!
  dist_raw = (6762.0/(a_value-9)-4.0)*10.0 - 6.0;
  if (dist_raw < _DIST_MIN) {
    dist_raw=dist_prev;
    duty = _DUTY_MIN;
  }
  else if (dist_raw > _DIST_MAX) {
    dist_raw=dist_prev;
    duty = _DUTY_MAX;
  }
 
    
  // Apply ema filter here  
  ema = (alpha*dist_raw)+(1-alpha)*ema;// we need EMA filter here !!!
  dist_prev=dist_raw;
  if(ema < 100){digitalWrite(PIN_LED,1);}
     else if(ema>250){digitalWrite(PIN_LED,1);}
     else{digitalWrite(PIN_LED,0);}
  
  // map distance into duty
  duty = ((_DUTY_MAX-_DUTY_MIN)/150)*(ema-100)+_DUTY_MIN;
  myservo.writeMicroseconds(duty);

  // print IR sensor value, distnace, duty !!!
  Serial.print("MIN: "); Serial.print(_DIST_MIN);
  Serial.print(",IR:");  Serial.print(a_value);
  Serial.print(",ema:"); Serial.print(ema);
  Serial.print(",servod:"); Serial.print(duty);
  Serial.print(",MAX:");  Serial.print(_DIST_MAX);
  Serial.println("dist_raw"); Serial.println(dist_raw);
}
