#include<stdlib.h>
#include<stdio.h>
#include<wiringPi.h>

#define DHT11   7
#define Heating 5

int ReadSensorData(void);   
int ConvertAndCheck(void);

short Humidity[16];         //storage humidity data
short Temperature[16];      //storage temperature data
short Check[8];             //storage check data
int TemperatureValue,HumidityValue;

int main()
{
    FILE *fp;

    wiringPiSetup();

    pinMode(DHT11|Heating,OUTPUT);
    digitalWrite(DHT11|Heating,HIGH);

    //while(1)
    //{
        fp = fopen("DHT11.txt","w");
        
//        pinMode(DHT11,OUTPUT);
//        digitalWrite(DHT11,HIGH);
        delay(3000);
        fp = fopen("DHT11.txt","w");

        if(ReadSensorData())
        {
            ConvertAndCheck();
            if(TemperatureValue < 30)
                digitalWrite(Heating,LOW);
            if(fp != NULL)
                fprintf(fp,"The Temperature is %d°C,the Humidity is %d %%RH\n",TemperatureValue,HumidityValue);
            printf("The Temperature is %d°C,the Humidity is %d %%RH\n",TemperatureValue,HumidityValue);
        }
        else if(!ReadSensorData())
        {
                system("echo Sensor no response!");
                system("exit");
                //break;
        }       
        else
        {}
        
        fclose(fp);
    //}
       
    return 0;
}


int ReadSensorData(void)
{
    short dataByte,checkByte;
    short HumidityOrTemperature = 0;

    //procedure 1
    pinMode(DHT11,OUTPUT);
    digitalWrite(DHT11,LOW);
    delay(25);
    digitalWrite(DHT11,HIGH);
    pinMode(DHT11,INPUT);
    //procedure 2
    delayMicroseconds(27);
    if(!digitalRead(DHT11))          //receive answer signal
    {
        while(!digitalRead(DHT11));  //wait for answer signal end
        //start recive data
        /*if the format just like (first 50us low level and then 26~28us high level),
          it means '1',if the format just like (first 50us low level and then 70us high level),
          it means '0'*/
        //recive temprature data and humidity data
        for(dataByte = 0;dataByte <= 16;dataByte++)
        {
            if(HumidityOrTemperature==0 && dataByte==16)
            {
                dataByte = 0;
                HumidityOrTemperature = 1;
            }
            while(digitalRead(DHT11));  //wait for prepare signal end
            while(!digitalRead(DHT11));
            delayMicroseconds(30);
            if(digitalRead(DHT11)==1)
            {
                if(HumidityOrTemperature==0)
                    Humidity[dataByte] = 1;
                else if(HumidityOrTemperature==1)
                    Temperature[dataByte] = 1;
                else
                {}
            }
            else if(digitalRead(DHT11)==0)
            {
                if(HumidityOrTemperature==0)
                    Humidity[dataByte] = 0;
                else if(HumidityOrTemperature==1)
                    Temperature[dataByte] = 0;
                else
                {}
            }  
            else
            {}
        
        }
        //recive check data
        for(checkByte = 0;checkByte < 8;checkByte++)
        {
            while(digitalRead(DHT11));  //wait for prepare signal end
            while(!digitalRead(DHT11));
            delayMicroseconds(30);
            if(digitalRead(DHT11)==1)
                Check[checkByte] = 1;
            else if(digitalRead(DHT11)==0)
                Check[checkByte] = 0;
            else
            {}
        
        }
        return 1;
    }
    return 0;
}

int ConvertAndCheck(void)
{
    short convert;
    short CheckValue;

    TemperatureValue = HumidityValue = 0;

    for(convert = 7;convert >= 0;convert--)
    {
        if(Humidity[convert] == 1)
            HumidityValue += (0x80>>convert);
        else if(Humidity[convert] == 0)
            HumidityValue += 0;
        else
        {}

        if(Temperature[convert] == 1)
            TemperatureValue += (0x80>>convert);
        else if(Humidity[convert] == 0)
            TemperatureValue += 0;
        else
        {}

        if(Check[convert] == 1)
            CheckValue += (0x80>>convert);
        else if(Check[convert] == 0)
            CheckValue += 0;
        else
        {}    
    }
    //start check if the temperature and humodity data correct
    if(CheckValue!=(TemperatureValue + HumidityValue))
        return 1;
    else
        return 0;
}