#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>

#define CLOCKWISE 1
#define ANTICLOCKWISE 0
#define PI 3.141593

//Declarations for encoders & motors
AnalogInputPin lightSensor(FEHIO::P0_4);

DigitalInputPin frontBump(FEHIO::P1_0);

DigitalEncoder right_encoder(FEHIO::P0_0);
DigitalEncoder left_encoder(FEHIO::P0_1);

FEHMotor right_motor(FEHMotor::Motor0,9.0);
FEHMotor left_motor(FEHMotor::Motor1,9.0);


//Using shaft encoders
void move_forward(int percent, float distance) //using encoders
{
    int counts = distance*318/(2*PI*1.25);
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

//Zero radius rotation
void rotate(int angle,int direction, int percent)
{
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    int counts = (angle*3.4*318)/(360*1.25);
    if(direction==CLOCKWISE){
        left_motor.SetPercent(percent);
        right_motor.SetPercent(-percent);
        while((left_encoder.Counts() + right_encoder.Counts()) / 2.<counts);
    }
    else{
        left_motor.SetPercent(-percent);
        right_motor.SetPercent(percent);
        while((left_encoder.Counts() + right_encoder.Counts()) / 2.<counts);
    }
    left_motor.Stop();
    right_motor.Stop();
}

//Using bump switch
void bump_move(int percent)
{
    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);

    while(frontBump.Value());

    left_motor.Stop();
    right_motor.Stop();
}

int main(void)
{
    int motor_percent = 30; //Input power level here
    float threshold = 0.6;

    //Initialize the screen
    LCD.Clear(BLACK);
    LCD.SetFontColor(WHITE);

    LCD.WriteLine("Until the light shines bright,");
    LCD.WriteLine("I shall not do shyte");

    while(lightSensor.Value()>threshold);

    //Insert movement code (function calls)


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
