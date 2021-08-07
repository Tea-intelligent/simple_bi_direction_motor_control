//used pins
#define enA 9
#define in1 7
#define in2 6
#define incr 2
#define decr 3
#define dic 4
//speed limit
#define minSpeed 0
#define maxSpeed 10
//variable
const int bin1 = 0;
const int bin2 = 1;
int rotDirection = 0;
int pressed = false;
int* myspeed = new int;
int currentstate = 0;//current button state
int laststate = 0;//last button state
//---------------------------------------------------------
void setup() {
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(enA, OUTPUT);
    pinMode(incr, INPUT_PULLUP);
    pinMode(decr, INPUT_PULLUP);
    pinMode(dic, INPUT_PULLUP);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    attachInterrupt(0, faster, FALLING);
    attachInterrupt(1, slower, FALLING);
    *myspeed = 10;
    Serial.begin(9600);
}

void faster() {
    *myspeed = *myspeed + 1;
}

void slower() {
    *myspeed = *myspeed - 1;
}

void roll(int direct) {
    if (direct == 0) {
        digitalWrite(in1, bin1);
        digitalWrite(in2, bin2);
    }
    if (direct != 0) {
        digitalWrite(in1, bin2);
        digitalWrite(in2, bin1);
    }

}

void loop() {
    /*while(*myspeed<5){
      int temp_speed=map (5,0,10,0,255);
      analogWrite(enA,temp_speed);
    }*/
    *myspeed = constrain(*myspeed, minSpeed, maxSpeed);
    int pwmoutput = map(*myspeed, 0, 10, 0, 255);
    analogWrite(enA, pwmoutput);

    //direction button set up
    currentstate = digitalRead(dic);
    if (currentstate != laststate) {
        if (currentstate == HIGH) {
            rotDirection = !rotDirection;
        }
        delay(50);
    }
    laststate = currentstate;
    roll(rotDirection);

}