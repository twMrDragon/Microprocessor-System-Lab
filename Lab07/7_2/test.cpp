#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <string>

#define LED1 466
#define LED2 255
#define LED3 481
#define LED4 254

using namespace std;

void setGPIO(unsigned int gpio, string status)
{
    int io = open("/dev/demo", O_WRONLY);
    if (io < 0)
    {
        perror("gpio error");
        return;
    }
    char buf[10] = {0};
    if (status == "on")
    {
        strcpy(buf, (to_string(gpio) + "1").c_str());
    }
    else
    {
        strcpy(buf, (to_string(gpio) + "0").c_str());
    }
    write(io, buf, 10);
    close(io);
    return;
}

int getGPIO(unsigned int gpio)
{
    int io = open("/dev/demo", O_RDONLY);
    if (io < 0)
    {
        perror("gpio error");
        return -1;
    }
    char buf[10] = {0};
    strcpy(buf, to_string(gpio).c_str());
    buf[3] = 0;
    read(io, buf, 10);
    close(io);
    return (int)buf[0]-'0';
}

int main(int argc, char **argv)
{
    map<string, int> gpioPinMap = {
        {"LED1", LED1},
        {"LED2", LED2},
        {"LED3", LED3},
        {"LED4", LED4}};
    // cout << argv[1] << " " << argv[2] << endl;

    if (argc == 2)
    {
        // read led status
        int value = getGPIO(gpioPinMap[argv[1]]);
        printf("%s status: %d\n", argv[1], value);
        return 0;
    }
    if (argc == 3)
    {
        // set led status
        setGPIO(gpioPinMap[argv[1]], argv[2]);
        return 0;
    }
    perror("missing arg");
    return 0;
}