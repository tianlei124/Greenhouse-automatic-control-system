#include<stdio.h>
#include<stdlib.h>
#include<wiringPi.h>

#define Orange   5
#define Yellow   4
#define Pink     2
#define Blue     0

char CCW[] = {0x08,0x04,0x02,0x01};
char CW [] = {0x01,0x02,0x04,0x08};

void run(char RoF,short speed);         //'F' means Forward,'R' means Reverse

int main()
{
    char HowToRun = 'F';

    wiringPiSetup();

    pinMode(Blue|Pink|Yellow|Orange,OUTPUT);
    digitalWrite(Blue|Pink|Yellow|Orange,LOW);

    while(1)
    {
        run(HowToRun,(30000/4096));
    }

    return 0;
}

void run(char RoF,short speed)
{
    short OneCycle;

    if(RoF=='F')
    {
        for(OneCycle = 0;OneCycle < 4;OneCycle++)
        {
            digitalWrite(Blue,(CW[OneCycle]>>0)&0x01);
            digitalWrite(Pink,(CW[OneCycle]>>1)&0x01);
            digitalWrite(Yellow,(CW[OneCycle]>>2)&0x01);
            digitalWrite(Orange,(CW[OneCycle]>>3)&0x01); 

            delay(speed);
        }
    }
    else if(RoF=='R')    
    {
        for(OneCycle = 0;OneCycle < 4;OneCycle++)
        {
            digitalWrite(Blue,(CCW[OneCycle]>>0)&0x01);
            digitalWrite(Pink,(CCW[OneCycle]>>1)&0x01);
            digitalWrite(Yellow,(CCW[OneCycle]>>2)&0x01);
            digitalWrite(Orange,(CCW[OneCycle]>>3)&0x01);    
        
            delay(speed);
        }
    }
    else
    {
        digitalWrite(Orange,LOW);
        digitalWrite(Yellow,LOW);
        digitalWrite(Pink,LOW);
        digitalWrite(Blue,LOW);    
    }
}