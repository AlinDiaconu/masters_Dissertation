float verificaDistanta()
{
    digitalWrite(12, LOW);
    delayMicroseconds(2);
    digitalWrite(12, HIGH);
    delayMicroseconds(10);
    digitalWrite(12, LOW);
    float distanta = pulseIn(13, HIGH) / 58.00;
    delay(10);
    return distanta;
}

void Modul_Senzor_Ultrasonic()
{
    int Distanta = 0;
    Distanta = verificaDistanta();
    Serial.print("Distanta:");
    Serial.print(Distanta);
    Serial.println("CM");
    delay(100);
}

void setup()
{
    Serial.begin(9600);
    pinMode(12, OUTPUT);
    pinMode(13, INPUT);
}

void loop()
{
    Modul_Senzor_Ultrasonic();
}
