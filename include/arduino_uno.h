#ifndef MASTERS_DISSERTATION_ARDUINO_UNO_H
#define MASTERS_DISSERTATION_ARDUINO_UNO_H
#include <Servo.h>
#include <Arduino.h>

// Controlul pinilor de servo
#define MOTOR_PIN           9
// PWM control pin
#define PWM1_PIN            5
#define PWM2_PIN            6
// pinul cipului 74HCT595N
#define SHCP_PIN            2                               // Deplasarea ceasului
#define EN_PIN              7                               // Poate face controlul
#define DATA_PIN            8                               // Serial data
#define STCP_PIN            4                               // Ceas de registru de memorie
#define Trig_PIN            12
#define Echo_PIN            13
#define LEFT_LINE_TRACJING      A0
#define CENTER_LINE_TRACJING    A1
#define right_LINE_TRACJING     A2

Servo MOTORservo;

const int Forward       = 92;                               // Inainte
const int Backward      = 163;                              // Inapoi
const int Turn_Left     = 149;                              // Translatie stanga
const int Turn_Right    = 106;                              // Translatie dreapta
const int Top_Left      = 20;                               // Diagonala stanga sus
const int Bottom_Left   = 129;                              // Diagonala stanga jos
const int Top_Right     = 72;                               // Diagonala dreapta sus
const int Bottom_Right  = 34;                               // Diagonala dreapta jos
const int Stop          = 0;                                // Oprire
const int Contrarotate  = 172;                              // Rotatie trigonometrica
const int Clockwise     = 83;                               // Rotatie in sens orar
const int Application1        = 25;                               // Aplicatie 1
const int Application2        = 26;                               // Aplicatie 2
const int Application3        = 27;                               // Aplicatie 3
const int Application4        = 28;                               // Aplicatie 4
const int MotorLeft     = 230;                              // Motor servo stanga
const int MotorRight    = 231;                              // Motor servo dreapta

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
float SR04(int Trig, int Echo)      // Masuratoare distanta senzor ultrasonic
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
