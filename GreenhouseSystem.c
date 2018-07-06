#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

int main()
{
    FILE *fp;
    char wea[128];

    fp = popen("python3 weather.py", "r");
    fgets(wea, sizeof(wea), fp);
    pclose(fp);

    printf("%s\n", wea);

    return 0;
}
