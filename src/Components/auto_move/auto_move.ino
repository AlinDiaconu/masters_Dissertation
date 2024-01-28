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
const int Rotatie_Orara   = 172;                              // rotație în sensul acelor de ceas
const int Rotatie_Antiorara= 83;                               // rotație în sensul invers acelor de ceas

void setup()
{
    pinMode(SHCP_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
    pinMode(STCP_PIN, OUTPUT);
    pinMode(PWM1_PIN, OUTPUT);
    pinMode(PWM2_PIN, OUTPUT);
}

void loop()
{
    /* Înainte */
    Motor(Inainte, 250);     
    delay(2000);
    /* Înapoi */
    Motor(Inapoi, 250);
    delay(2000);
    /* Viraj_Stanga */
    Motor(Viraj_Stanga, 250);
    delay(2000);
    /* Viraj_Dreapta */
    Motor(Viraj_Dreapta, 250);
    delay(2000);
    /* Sus_Stanga */
    Motor(Sus_Stanga, 250);
    delay(2000);
    /* Jos_Dreapta */
    Motor(Jos_Dreapta, 250);
    delay(2000);
    /* Jos_Stanga */
    Motor(Jos_Stanga, 250);
    delay(2000);
    /* Sus_Dreapta */
    Motor(Sus_Dreapta, 250);
    delay(2000);
    /* Rotatie_Antiorara */
    Motor(Rotatie_Antiorara, 250);
    delay(2000);
    /* Rotatie_Orara */
    Motor(Rotatie_Orara, 250);
    delay(2000);
    /* Oprire */
    Motor(Oprire, 250);
    delay(2000);
}

void Motor(int Directie, int Viteza)
{
    digitalWrite(EN_PIN, LOW);
    analogWrite(PWM1_PIN, Viteza);
    analogWrite(PWM2_PIN, Viteza);

    digitalWrite(STCP_PIN, LOW);
    shiftOut(DATA_PIN, SHCP_PIN, MSBFIRST, Directie);
    digitalWrite(STCP_PIN, HIGH);
}
