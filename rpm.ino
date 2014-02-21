/* sketch to measure RPM
  Use the int0 to trigger interrupt to read counter values.
  This to occur for each revolution of the motor.
*/

#define Sensor 2  // int0

int  low_c = 0;
int  hgh_c = 0;
unsigned int rpm_i;
float rpm_f;

void setup(){
  
  pinMode(Sensor,INPUT);
  pinMode(13,OUTPUT);
  
  Serial.begin(9600);
  Serial.println("start");
  TCCR1A = 0x0;    // set mode
  TCCR1B = 0x04;   //set mode and counter prescale to 256
  
  attachInterrupt(0, rpm, FALLING);
  interrupts();
}

void loop(){
  
  Serial.print("RPM -> ");
  rpm_i = (hgh_c * 256 + low_c);
  rpm_f = (1/(float(rpm_i)*0.000016))*60;
  Serial.println(rpm_f);
  delay(100);
}

void rpm(){
// grab the coounter values on interrupt
  noInterrupts();
  low_c = TCNT1L;
  hgh_c = TCNT1H;
  TCNT1H = 0;    // reset high and low count to 0
  TCNT1L = 0; 
  interrupts();
}
