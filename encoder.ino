#define DEBUG  1

int pinA = 2;
int pinB = 3;
int pinC = 21;
int value = 0;

int oldAB = 0; // Remember old encoder values A and B
int stepTab[16] = {0,0,1,0,0,0,0,-1,0,0,0,1,0,0,-1,0}; // Lookup table for encoder steps 1/2
long steps = 0;
bool state = false;

void setup() {
    pinMode(pinA, INPUT);
    pinMode(pinB, INPUT);
    pinMode(pinC, INPUT);
    pinMode(13, OUTPUT);
    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, HIGH);
    digitalWrite(pinC, HIGH);
    attachInterrupt(digitalPinToInterrupt(pinA), readEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(pinB), readEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(pinC), blink, FALLING);
    Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void readEncoder() {
    oldAB <<= 2;
    oldAB &= 0x0C;
    oldAB |= (digitalRead(pinA) << 1) | digitalRead(pinB);
    steps += stepTab[oldAB];
#if DEBUG
    if  (value != steps) {
       Serial.println(steps);
       value = steps;
    }
#endif
}

void blink() {
     state = !state;
     digitalWrite(13, state);
#if DEBUG
     if (state) {
       Serial.println("Schnecke");
     } else {
       Serial.println("Hase");
     }
#endif
}
