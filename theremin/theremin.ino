/*
 *  HC-SR04 test2.
 *  Calibrating the sensor before using it for the theremin.
 *  This code is for TWO HC-SR04 sensors.
 *  Author: Tsz Kiu Pang
 *  Modified from
 *  https://www.instructables.com/id/Simple-Arduino-and-HC-SR04-Example/
 *  Date: 16/05/2019
 */

#define trig1Pin 13
#define echo1Pin 12
#define trig2Pin 11
#define echo2Pin 10

#define SPEED_OF_SOUND 343.0
#define CENTIMETERS 100.0
#define MICRO_SEC 1000000.0

const float dist_coeff = SPEED_OF_SOUND * CENTIMETERS / MICRO_SEC / 2.0;

void setup() {
    Serial.begin(9600);
    pinMode(trig1Pin, OUTPUT);
    pinMode(echo1Pin, INPUT);
    pinMode(trig2Pin, OUTPUT);
    pinMode(echo2Pin, INPUT);
}

void loop() {
    static byte out1 = 0, out2 = 0;
    long dur1, dur2;
    long dist1, dist2;

    digitalWrite(trig1Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig1Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig1Pin, LOW);
    dur1 = pulseIn(echo1Pin, HIGH);

    digitalWrite(trig2Pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig2Pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig2Pin, LOW);
    dur2 = pulseIn(echo2Pin, HIGH);

    dist1 = long(dur1 * dist_coeff);
    dist2 = long(dur2 * dist_coeff);

    if (dist1 < 200 && dist1 > 0) {
        out1 = map(dist1, 0, 200, 0, 127);
    }
    if (dist2 < 200 && dist2 > 0) {
        out2 = map(dist2, 0, 200, 128, 255);
    }
    Serial.write(out1);
    Serial.write(out2);
    delay(100);
}
