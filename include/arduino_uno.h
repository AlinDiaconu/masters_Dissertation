#ifndef MASTERS_DISSERTATION_ARDUINO_UNO_H
#define MASTERS_DISSERTATION_ARDUINO_UNO_H
#include <Servo.h>
#include <Arduino.h>

// servo control pin
#define MOTOR_PIN           9
// PWM control pin
#define PWM1_PIN            5
#define PWM2_PIN            6
// 74HCT595N chip pin
#define SHCP_PIN            2                               // The displacement of the clock
#define EN_PIN              7                               // Can make control
#define DATA_PIN            8                               // Serial data
#define STCP_PIN            4                               // Memory register clock
#define Trig_PIN            12
#define Echo_PIN            13
#define LEFT_LINE_TRACJING      A0
#define CENTER_LINE_TRACJING    A1
#define right_LINE_TRACJING     A2

Servo MOTORservo;

const int Forward       = 92;                               // forward
const int Backward      = 163;                              // back
const int Turn_Left     = 149;                              // left translation
const int Turn_Right    = 106;                              // Right translation
const int Top_Left      = 20;                               // Upper left mobile
const int Bottom_Left   = 129;                              // Lower left mobile
const int Top_Right     = 72;                               // Upper right mobile
const int Bottom_Right  = 34;                               // The lower right move
const int Stop          = 0;                                // stop
const int Contrarotate  = 172;                              // Counterclockwise rotation
const int Clockwise     = 83;                               // Rotate clockwise
const int Moedl1        = 25;                               // model1
const int Moedl2        = 26;                               // model2
const int Moedl3        = 27;                               // model3
const int Moedl4        = 28;                               // model4
const int MotorLeft     = 230;                              // servo turn left
const int MotorRight    = 231;                              // servo turn right

int Left_Tra_Value;
int Center_Tra_Value;
int Right_Tra_Value;
int Black_Line = 400;

int leftDistance = 0;
int middleDistance = 0;

int rightDistance = 0;
byte RX_package[3] = {0};
uint16_t angle = 90;
byte order = Stop;
char model_var = 0;

int UT_distance = 0;
float SR04(int Trig, int Echo)      // ultrasonic measured distance
{
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);
    float distance = pulseIn(Echo, HIGH) / 58.00;
    delay(10);

    return distance;
}
#endif //MASTERS_DISSERTATION_ARDUINO_UNO_H
