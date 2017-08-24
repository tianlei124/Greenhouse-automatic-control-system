#include<stdio.h>
#include<stdlib.h>
#include<wiringPi.h>

#define DO_Sensor   3
#define DI_Light    1

void SteplessAdjust(char BoD);

int bright = 512;

int main(void)
{
    wiringPiSetup();

    pinMode(DO_Sensor,INPUT);
    
    pinMode(DI_Light,PWM_OUTPUT);

    while(1)
    {
        if(!digitalRead(DO_Sensor))
            SteplessAdjust('D');
        if(digitalRead(DO_Sensor))
            SteplessAdjust('B');
    }

    return 0;
}

void SteplessAdjust(char BoD)
{
    if(BoD=='B')
    {
        pwmWrite(DI_Light,bright);
        bright++;
        delay(12);
        if(bright == 1024)
            bright = 1023;
    }
    else if(BoD=='D')
    {
        pwmWrite(DI_Light,bright);
        bright--;
        delay(12);
        if(bright < 0)
            bright = 0;
    }
    else
    {}
}