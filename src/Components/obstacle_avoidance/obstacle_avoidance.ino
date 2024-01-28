#include <Servo.h>  // biblioteca pentru servo
Servo myservo;      // creare obiect servo pentru controlul servoului
// Pin de control pentru senzorul ultrasonic
const int Trig = 12;
const int Echo = 13;
// Pin de control pentru PWM
#define PWM1_PIN            5
#define PWM2_PIN            6      
// Pini pentru cipul 74HCT595N
#define SHCP_PIN            2                               // Deplasarea ceasului
#define EN_PIN              7                               // Controlul poate fi activat/dezactivat
#define DATA_PIN            8                               // Date seriale
#define STCP_PIN            4                               // Ceasul registrului de memorie                  

const int Inainte         = 92;                               // înainte
const int Inapoi          = 163;                              // înapoi
const int Viraj_Stanga    = 149;                              // viraj la stânga
const int Viraj_Dreapta   = 106;                              // viraj la dreapta 
const int Sus_Stanga      = 20;                               // sus stânga
const int Jos_Stanga      = 129;                              // jos stânga
const int Sus_Dreapta     = 72;                               // sus dreapta
const int Jos_Dreapta     = 34;                               // jos dreapta
const int Oprire          = 0;                                // oprire
const int Contrarotatie   = 172;                              // rotație în sens invers acelor de ceas
const int Rotatie         = 83;                               // rotație în sensul acelor de ceas

int distantaDreapta = 0, distantaStanga = 0, distantaMijloc = 0;

float SR04(int Trig, int Echo)
{
    digitalWrite(Trig, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(Trig, LOW);
    float distanta = pulseIn(Echo, HIGH) / 58.00;
    delay(10);
    return distanta;
}

void setup()
{
    myservo.attach(9, 700, 2400); // atașare servo pe pinul 9 la obiectul servo
    pinMode(Trig, OUTPUT);
    pinMode(Echo, INPUT);

    pinMode(SHCP_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
    pinMode(STCP_PIN, OUTPUT);
    pinMode(PWM1_PIN, OUTPUT);
    pinMode(PWM2_PIN, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    distantaMijloc = SR04(Trig, Echo);
    Serial.print("Distanta:");
    Serial.println(distantaMijloc);
    if (distantaMijloc <= 25) 
    {
        Motor(Oprire, 0);
        delay(500);
        myservo.write(10);
        delay(500);
        distantaDreapta = SR04(Trig, Echo);

        delay(500);
        myservo.write(90);
        delay(500);
        myservo.write(170);
        delay(500);
        distantaStanga = SR04(Trig, Echo);

        delay(500);
        myservo.write(90);
        delay(500);
     
        if(distantaDreapta > distantaStanga){
            Motor(Oprire, 0);
            delay(100);
            Motor(Inapoi, 180);
            delay(1000);
            Motor(Rotatie, 250); 
            delay(600);
        }
        else if(distantaDreapta < distantaStanga) {
            Motor(Oprire, 0);
            delay(100);
            Motor(Inapoi, 180);
            delay(1000);
            Motor(Contrarotatie, 250);
            delay(600);
        }
        else if((distantaDreapta < 20) || (distantaStanga < 20)){
            Motor(Inapoi, 180);
            delay(1000);
            Motor(Contrarotatie, 250); 
            delay(600);
        }
        else{
            Motor(Inapoi, 180);
            delay(1000);
            Motor(Rotatie, 250); 
            delay(600);
        }
    }
    else 
    {
        Motor(Inainte, 250);
    }
}

void Motor(int Dir, int Viteza)
{
    analogWrite(PWM1_PIN, Viteza);
    analogWrite(PWM2_PIN, Viteza);

    digitalWrite(STCP_PIN, LOW);
    shiftOut(DATA_PIN, SHCP_PIN, MSBFIRST, Dir);
    digitalWrite(STCP_PIN, HIGH);
}
