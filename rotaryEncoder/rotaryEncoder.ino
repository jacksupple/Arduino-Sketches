// simple rotary encoder interrupt

//////// encoder params ////////
#define S1_pin    A0
#define S2_pin    A1
#define key_pin   A2

volatile int rotCounter = 0;
volatile int S1_state;
volatile int prev_S1_state;
volatile int key_state;

void setup(){
  pinMode(S1_pin,INPUT);
  pinMode(S2_pin,INPUT);
  pinMode(key_pin,INPUT_PULLUP);
  
  PCICR  |= B00000010; // pin change interrupt control register. Enable PCMSK1
  PCMSK1 |= B00000101; // Enable interrupt on PCINT8 and PCINT9 (pin A0 and A2 in group1)

  Serial.begin(9600);
  prev_S1_state = PINC & B00000001; // digital read pin A0
  
}

// ISR for port C
ISR(PCINT1_vect){

  key_state = digitalRead(key_pin);
  S1_state = digitalRead(S1_pin);

  if (S1_state != prev_S1_state){
    if(digitalRead(S2_pin) != S1_state){
      rotCounter ++;
    } else {
      rotCounter --;
    }
  }
  prev_S1_state = S1_state;
  
}


void loop(){
  Serial.print(key_state);       Serial.print(", ");
  Serial.print(S1_state);       Serial.print(", ");
  Serial.print(prev_S1_state);  Serial.print(", ");
  Serial.println(rotCounter/2);
}
