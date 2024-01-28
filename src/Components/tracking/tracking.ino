// Pin de control pentru PWM
#define PWM1_PIN            5
#define PWM2_PIN            6      
// Pinuri pentru cipul 74HCT595N
#define SHCP_PIN            2                               // Deplasarea ceasului
#define EN_PIN              7                               // Poate realiza controlul
#define DATA_PIN            8                               // Date seriale
#define STCP_PIN            4                               // Ceasul registrului de memorie          

#define LEFT_LINE_TRACJING          A0
#define CENTER_LINE_TRACJING        A1
#define RIGHT_LINE_TRACJING         A2

const int Inainte       = 92;                               // înainte
const int Inapoi        = 163;                              // înapoi
const int Viraj_Stanga  = 149;                              // viraj la stânga
const int Viraj_Dreapta = 106;                              // viraj la dreapta 
const int Sus_Stanga    = 20;                               // sus stânga
const int Jos_Stanga    = 129;                              // jos stânga
const int Sus_Dreapta   = 72;                               // sus dreapta
const int Jos_Dreapta   = 34;                               // jos dreapta
const int Oprire        = 0;                                // oprire
const int Contrarotire  = 172;                              // rotație în sens invers acelor de ceas
const int Rotire        = 83;                               // rotație în sensul acelor de ceas

int Valoare_Trasa_Stanga;
int Valoare_Trasa_Centru;
int Valoare_Trasa_Dreapta;
int Linie_Neagra = 500;

void setup()
{
    pinMode(SHCP_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
    pinMode(STCP_PIN, OUTPUT);
    pinMode(PWM1_PIN, OUTPUT);
    pinMode(PWM2_PIN, OUTPUT);

    pinMode(LEFT_LINE_TRACJING, INPUT);
    pinMode(CENTER_LINE_TRACJING, INPUT);
    pinMode(RIGHT_LINE_TRACJING, INPUT);
}

void loop()
{
    Valoare_Trasa_Stanga = analogRead(LEFT_LINE_TRACJING);
    Valoare_Trasa_Centru = analogRead(CENTER_LINE_TRACJING);
    Valoare_Trasa_Dreapta = analogRead(RIGHT_LINE_TRACJING);
    if (Valoare_Trasa_Stanga < Linie_Neagra && Valoare_Trasa_Centru >= Linie_Neagra && Valoare_Trasa_Dreapta < Linie_Neagra)
    {
        Motor(Inainte, 250);//175
    }
    else if (Valoare_Trasa_Stanga >= Linie_Neagra && Valoare_Trasa_Centru >= Linie_Neagra && Valoare_Trasa_Dreapta < Linie_Neagra)
    {
        Motor(Contrarotire, 230);//165
    }
    else if (Valoare_Trasa_Stanga >= Linie_Neagra && Valoare_Trasa_Centru < Linie_Neagra && Valoare_Trasa_Dreapta < Linie_Neagra)
    {
        Motor(Contrarotire, 250);//190
    }
    else if (Valoare_Trasa_Stanga < Linie_Neagra && Valoare_Trasa_Centru < Linie_Neagra && Valoare_Trasa_Dreapta >= Linie_Neagra)
    {
        Motor(Rotire, 250);//190
    }
    else if (Valoare_Trasa_Stanga < Linie_Neagra && Valoare_Trasa_Centru >= Linie_Neagra && Valoare_Trasa_Dreapta >= Linie_Neagra)
    {
        Motor(Rotire, 230);//165
    }
    else if (Valoare_Trasa_Stanga >= Linie_Neagra && Valoare_Trasa_Centru >= Linie_Neagra && Valoare_Trasa_Dreapta >= Linie_Neagra)
    {
        Motor(Oprire, 0);
    }
}

void Motor(int Dir, int Viteza)
{
    digitalWrite(EN_PIN, LOW);
    analogWrite(PWM1_PIN, Viteza);
    analogWrite(PWM2_PIN, Viteza);

    digitalWrite(STCP_PIN, LOW);
    shiftOut(DATA_PIN, SHCP_PIN, MSBFIRST, Dir);
    digitalWrite(STCP_PIN, HIGH);
}
