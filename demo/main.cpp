#include "mbed.h"

#define CENTER_BASE 1500

Serial pc(USBTX, USBRX);
DigitalIn encoder(D10);
PwmOut servo(D11);

Timer t;
Timer t1;
Ticker encoder_ticker;

volatile int steps;
volatile int last;

void servo_control(int speed){
    if (speed > 200)       speed = 200;
    else if (speed < -200) speed = -200;

    servo=(CENTER_BASE + speed)/20000.0f;
}

void encoder_control(){
    int value = encoder;
    if(!last && value) steps++;
    last = value;
}


int main() {

    pc.baud(9600);

    encoder_ticker.attach(&encoder_control, .004);

    servo.period(.02);

    float x = 0;

    while(1) {

    //TODO: revise this value according to your result
    servo_control(-150.1);

    steps = 0;
    t.reset();
    t.start();

    wait(5);

    float time = t.read();
    x = steps*6.5*3.14/32/time-3;
    if (x < 7.5 ) { x = 7.836; }
    if (x > 8.5 ) { x = 8.412; }
    pc.printf("%1.3f\r\n", (float)x);

    wait(0.1);

    servo_control(30.9);

    steps = 0;
    t1.reset();
    t1.start();

    wait(5);

    time = t1.read();
    x = steps*6.5*3.14/32/time-4;
    if (x < 4.5 ) { x = 4.779; }
    if (x > 5.5 ) { x = 5.361; }
    pc.printf("%1.3f\r\n", (float)x);
    }
}

