#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>

#define CLOCKWISE 1
#define ANTICLOCKWISE 0
#define PI 3.141593

//Declarations for encoders & motors
AnalogInputPin lightSensor(FEHIO::P3_7);

DigitalInputPin frontBump(FEHIO::P1_0);

DigitalEncoder right_encoder(FEHIO::P0_1);
DigitalEncoder left_encoder(FEHIO::P0_0);

FEHMotor right_motor(FEHMotor::Motor1,9.0);
FEHMotor left_motor(FEHMotor::Motor0,9.0);


//Using shaft encoders
void move_forward(int lpercent, int rpercent, float distance) //using encoders
{
    int counts = distance*318/(2*PI*1.75);
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(rpercent);
    left_motor.SetPercent(lpercent);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

//Zero radius rotation
void rotate(int angle,int direction, int rpercent, int lpercent)
{
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    int counts = (angle*3.4*318*1.5)/(360*1.75);
    if(direction==CLOCKWISE){
        left_motor.SetPercent(lpercent);
        right_motor.SetPercent(-rpercent);
        while((left_encoder.Counts() + right_encoder.Counts()) / 2.<counts);
    }
    else{
        left_motor.SetPercent(-lpercent);
        right_motor.SetPercent(rpercent);
        while((left_encoder.Counts() + right_encoder.Counts()) / 2.<counts);
    }
    left_motor.Stop();
    right_motor.Stop();
}


int main(void)
{
    int right_motor_percent = -47; //Input power level here
    int left_motor_percent = -45;
    float threshold = 0.6;

    //Initialize the screen
    LCD.Clear(BLACK);
    LCD.SetFontColor(WHITE);

    LCD.WriteLine("Until the light shines bright,");
    LCD.WriteLine("I shall not do shyte");

    while(lightSensor.Value()>threshold);

    rotate(10,ANTICLOCKWISE,right_motor_percent,left_motor_percent);

    right_motor.SetPercent(right_motor_percent);
    left_motor.SetPercent(left_motor_percent);
    LCD.WriteLine(frontBump.Value());
    while(frontBump.Value()){}
    left_motor.Stop();
    right_motor.Stop();

    move_forward(-right_motor_percent,-left_motor_percent,1);
    rotate(100,CLOCKWISE,right_motor_percent,left_motor_percent);
    right_motor.SetPercent(right_motor_percent);
    left_motor.SetPercent(left_motor_percent);
    LCD.WriteLine(frontBump.Value());
    while(frontBump.Value()){}
    left_motor.Stop();
    right_motor.Stop();

    move_forward(-right_motor_percent,-left_motor_percent,3.5);
    rotate(70,ANTICLOCKWISE,right_motor_percent,left_motor_percent);
    move_forward(right_motor_percent,left_motor_percent,10);
    rotate(125,ANTICLOCKWISE,right_motor_percent,left_motor_percent);
    move_forward(right_motor_percent,left_motor_percent,3.5);
    move_forward(-right_motor_percent,-left_motor_percent,2);
    rotate(90,ANTICLOCKWISE,right_motor_percent,left_motor_percent);
    move_forward(right_motor_percent,left_motor_percent,8);
    rotate(50,ANTICLOCKWISE,right_motor_percent,left_motor_percent);
    move_forward(right_motor_percent,left_motor_percent,6);
    rotate(24,CLOCKWISE,right_motor_percent,left_motor_percent);
    move_forward(right_motor_percent,left_motor_percent,20);
    //rotate(90,ANTICLOCKWISE,right_motor_percent,left_motor_percent);

//    Sleep(2.0); //Wait for counts to stabilize
//    //Print out data
//    //LCD.Write("Theoretical Counts: ");
//    //LCD.WriteLine(expected_counts);
//    LCD.Write("Motor Percent: ");
//    LCD.WriteLine(motor_percent);
//    LCD.Write("Actual LE Counts: ");
//    LCD.WriteLine(left_encoder.Counts());
//    LCD.Write("Actual RE Counts: ");
//    LCD.WriteLine(right_encoder.Counts());

    return 0;
}
