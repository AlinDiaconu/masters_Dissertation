#include <arduino_uno.h>

void Motor(int Dir, int Speed)      // motor drive
{
    digitalWrite(EN_PIN, LOW);
    analogWrite(PWM1_PIN, Speed);
    analogWrite(PWM2_PIN, Speed);

    digitalWrite(STCP_PIN, LOW);
    shiftOut(DATA_PIN, SHCP_PIN, MSBFIRST, Dir);
    digitalWrite(STCP_PIN, HIGH);
}

void motorleft()  //servo
{
    MOTORservo.write(angle);
    angle+=1;
    if(angle >= 180) angle = 180;
    delay(10);
}

void motorright() //servo
{
    MOTORservo.write(angle);
    angle-=1;
    if(angle <= 1) angle = 1;
    delay(10);
}

void RXpack_func()  //Receive data
{
    if(Serial.available() > 0)
    {
        delay(1);                                           // delay 1MS
        if(Serial.readBytes(RX_package, 3))
        {
            if (RX_package[0] == 0xA5 && RX_package[2] == 0x5A)     // The include and tail of the packet are verified
            {
                order = RX_package[1];
                if(order == Moedl1)
                {
                    model_var = 0;
                }
                else if (order == Moedl2)
                {
                    model_var = 1;
                }
                else if (order == Moedl3)
                {
                    model_var = 2;
                }
                else if (order == Moedl4)
                {
                    model_var = 3;
                }
                //////////////////////////////
                // switch (RX_package[1])
                // {
                // case Stop:
                //     Serial.println("Stop");
                //     break;
                // case Forward:
                //     Serial.println("Forward");
                //     break;
                // case Backward:
                //     Serial.println("Backward");
                //     break;
                // case Turn_Left:
                //     Serial.println("Turn_Left");
                //     break;
                // case Turn_Right:
                //     Serial.println("Turn_Right");
                //     break;
                // case Top_Left:
                //     Serial.println("Top_Left");
                //     break;
                // case Bottom_Left:
                //     Serial.println("Bottom_Left");
                //     break;
                // case Top_Right:
                //     Serial.println("Top_Right");
                //     break;
                // case Bottom_Right:
                //     Serial.println("Bottom_Right");
                //     break;
                // case Clockwise:
                //     Serial.println("Clockwise");
                //     break;
                // case MotorLeft:
                //     Serial.println("MotorLeft");
                //     break;
                // case MotorRight:
                //     Serial.println("MotorRight");
                //     break;
                // case Moedl1:
                //     Serial.println("Moedl1");
                //     break;
                // case Moedl2:
                //     Serial.println("Moedl2");
                //     break;
                // case Moedl3:
                //     Serial.println("Moedl3");
                //     break;
                // case Moedl4:
                //     Serial.println("Moedl4");
                //     break;
                // default:
                //     break;
                // }
            }
        }
    }
}
void model1_func(byte orders)
{
    switch (orders)
    {
    case Stop:
        Motor(Stop, 0);
        break;
    case Forward:
        Motor(Forward, 250);
        break;
    case Backward:
        Motor(Backward, 250);
        break;
    case Turn_Left:
        Motor(Turn_Left, 250);
        break;
    case Turn_Right:
        Motor(Turn_Right, 250);
        break;
    case Top_Left:
        Motor(Top_Left, 250);
        break;
    case Top_Right:
        Motor(Top_Right, 250);
        break;
    case Bottom_Left:
        Motor(Bottom_Left, 250);
        break;
    case Bottom_Right:
        Motor(Bottom_Right, 250);
        break;
    case Clockwise:
        Motor(Clockwise, 250);
        break;
    case MotorLeft:
        motorleft();
        break;
    case MotorRight:
        motorright();
        break;
    default:
        // Serial.println(".");
        order = 0;
        Motor(Stop, 0);
        break;
    }
}
void model2_func()      // OA
{
    MOTORservo.write(90);
    UT_distance = SR04(Trig_PIN, Echo_PIN);
    Serial.println(UT_distance);
    middleDistance = UT_distance;

    if (middleDistance <= 25)
    {
        Motor(Stop, 0);
        for(int i = 0;i < 500;i++){
          delay(1);
          RXpack_func();
          if(model_var != 1)
            return ;
        }
        MOTORservo.write(10);
        for(int i = 0;i < 300;i++){
          delay(1);
          RXpack_func();
          if(model_var != 1)
            return ;
        }
        rightDistance = SR04(Trig_PIN, Echo_PIN);//SR04();
        Serial.print("rightDistance:  ");
        Serial.println(rightDistance);
        MOTORservo.write(90);
        for(int i = 0;i < 300;i++){
          delay(1);
          RXpack_func();
          if(model_var != 1)
            return ;
        }
        MOTORservo.write(170);
        for(int i = 0;i < 300;i++){
          delay(1);
          RXpack_func();
          if(model_var != 1)
            return ;
        }
        leftDistance = SR04(Trig_PIN, Echo_PIN);//SR04();
        Serial.print("leftDistance:  ");
        Serial.println(leftDistance);
        MOTORservo.write(90);
        if((rightDistance < 20) && (leftDistance < 20)){

            Motor(Backward, 180);
            for(int i = 0;i < 1000;i++){
              delay(1);
              RXpack_func();
              if(model_var != 1)
                return ;
            }
            Motor(Contrarotate, 250);
            for(int i = 0;i < 500;i++){
              delay(1);
              RXpack_func();
              if(model_var != 1)
                return ;
            }
        }
        else if(rightDistance < leftDistance) {
            Motor(Stop, 0);
            for(int i = 0;i < 100;i++){
              delay(1);
              RXpack_func();
              if(model_var != 1)
                return ;
            }
            Motor(Backward, 180);
            for(int i = 0;i < 500;i++){
              delay(1);
              RXpack_func();
              if(model_var != 1)
                return ;
            }
            Motor(Contrarotate, 250);
            for(int i = 0;i < 500;i++){
              delay(1);
              RXpack_func();
              if(model_var != 1)
                return ;
            }
        }//turn right
        else if(rightDistance > leftDistance){
            Motor(Stop, 0);
            for(int i = 0;i < 500;i++){
              delay(1);
              RXpack_func();
              if(model_var != 1)
                return ;
            }
            Motor(Backward, 180);
            for(int i = 0;i < 500;i++){
              delay(1);
              RXpack_func();
              if(model_var != 1)
                return ;
            }
            Motor(Clockwise, 250);
            for(int i = 0;i < 500;i++){
              delay(1);
              RXpack_func();
              if(model_var != 1)
                return ;
            }
        }
        else{
            Motor(Backward, 180);
            for(int i = 0;i < 500;i++){
              delay(1);
              RXpack_func();
              if(model_var != 1)
                return ;
            }
            Motor(Clockwise, 250);
            for(int i = 0;i < 500;i++){
              delay(1);
              RXpack_func();
              if(model_var != 1)
                return ;
            }
        }
    }
    else
    {
        Motor(Forward, 250);
    }
}

void model3_func()      // follow model
{
    MOTORservo.write(90);
    UT_distance = SR04(Trig_PIN, Echo_PIN);
    Serial.println(UT_distance);
    if (UT_distance < 15)
    {
        Motor(Backward, 200);
    }
    else if (15 <= UT_distance && UT_distance <= 20)
    {
        Motor(Stop, 0);
    }
    else if (20 <= UT_distance && UT_distance <= 25)
    {
        Motor(Forward, 180);
    }
    else if (25 <= UT_distance && UT_distance <= 50)
    {
        Motor(Forward, 220);
    }
    else
    {
        Motor(Stop, 0);
    }
}

void model4_func()      // tracking model
{
    MOTORservo.write(90);
    Left_Tra_Value = analogRead(LEFT_LINE_TRACJING);
    Center_Tra_Value = analogRead(CENTER_LINE_TRACJING);
    Right_Tra_Value = analogRead(right_LINE_TRACJING);
    if (Left_Tra_Value < Black_Line && Center_Tra_Value >= Black_Line && Right_Tra_Value < Black_Line)
    {
        Motor(Forward, 250);
    }
    else if (Left_Tra_Value >= Black_Line && Center_Tra_Value >= Black_Line && Right_Tra_Value < Black_Line)
    {
        Motor(Contrarotate, 220);
    }
    else if (Left_Tra_Value >= Black_Line && Center_Tra_Value < Black_Line && Right_Tra_Value < Black_Line)
    {
        Motor(Contrarotate, 250);
    }
    else if (Left_Tra_Value < Black_Line && Center_Tra_Value < Black_Line && Right_Tra_Value >= Black_Line)
    {
        Motor(Clockwise, 250);
    }
    else if (Left_Tra_Value < Black_Line && Center_Tra_Value >= Black_Line && Right_Tra_Value >= Black_Line)
    {
        Motor(Clockwise, 220);
    }
    else if (Left_Tra_Value >= Black_Line && Center_Tra_Value >= Black_Line && Right_Tra_Value >= Black_Line)
    {
        Motor(Stop, 0);
    }
}

void setup()
{
    Serial.setTimeout(10);
    Serial.begin(115200);

    MOTORservo.attach(MOTOR_PIN);

    pinMode(SHCP_PIN, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
    pinMode(STCP_PIN, OUTPUT);
    pinMode(PWM1_PIN, OUTPUT);
    pinMode(PWM2_PIN, OUTPUT);

    pinMode(Trig_PIN, OUTPUT);
    pinMode(Echo_PIN, INPUT);

    pinMode(LEFT_LINE_TRACJING, INPUT);
    pinMode(CENTER_LINE_TRACJING, INPUT);
    pinMode(right_LINE_TRACJING, INPUT);

    MOTORservo.write(angle);

    Motor(Stop, 0);
}

void loop()
{
    RXpack_func();
    switch (model_var)
    {
        case 0:
            model1_func(order);
            break;
        case 1:
            model2_func();      // OA model
            break;
        case 2:
            model3_func();      // follow model
            break;
        case 3:
            model4_func();      // Tracking model
            break;
    }

}
