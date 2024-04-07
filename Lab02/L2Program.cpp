#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <map>

#define LED1 466
#define LED2 255
#define LED3 481
#define LED4 254

using namespace std;

int gpio_export(unsigned int gpio);
int gpio_unexport(unsigned int gpio);
int gpio_set_dir(unsigned int gpio,string dirStatus);
int gpio_set_value(unsigned int gpio,int value);

int main(int argc,char *argv[]){
    if(argc<3){
        printf("missing arg\n");
        return 0;
    }

	map<string,int> gpioCodeMap = {
		{"LED1",LED1},
		{"LED2",LED2},
		{"LED3",LED3},
		{"LED4",LED4}
	};

	if(strcmp(argv[1],"Mode_shine")==0){
		// init 
		vector<int> v = {LED1,LED2,LED3,LED4};
		for(int gpioCode:v){
			gpio_export(gpioCode);
			gpio_set_dir(gpioCode,"out");
		}
		// shine
		int times = stoi(argv[2]);
		int flag = 1;
		for(int i=0;i<times*2;i++){
			gpio_set_value(LED1,flag);
			gpio_set_value(LED2,flag);
			gpio_set_value(LED3,!flag);
			gpio_set_value(LED4,!flag);
			flag = !flag;
			sleep(1);
		}
		for(int gpioCode:v){
			gpio_set_value(gpioCode,0);
		}
	}else{
		// toggle
		int gpioCode = gpioCodeMap[argv[1]];

		gpio_export(gpioCode);
		gpio_set_dir(gpioCode,"out");
		if(strcmp(argv[2],"on")==0){
			gpio_set_value(gpioCode,1);
		}else if(strcmp(argv[2],"off")==0){
			gpio_set_value(gpioCode,0);
		}
	}
}

int gpio_export(unsigned int gpio){
	int fd,len;
	char buf[64];
	fd = open("/sys/class/gpio/export",O_WRONLY);
	if(fd<0){
		perror("gpio/export");
		return fd;
	}
	len = snprintf(buf,sizeof(buf),"%d",gpio);
	write(fd,buf,len);
	close(fd);
	return 0;
}

int gpio_unexport(unsigned int gpio){
	int fd,len;
	char buf[64];
	fd = open("/sys/class/gpio/unexport",O_WRONLY);
	if(fd<0){
		perror("gpio/unexport");
		return fd;
	}
	len = snprintf(buf,sizeof(buf),"%d",gpio);
	write(fd,buf,len);
	close(fd);
	return 0;
}

int gpio_set_dir(unsigned int gpio,string dirStatus){
	int fd;
	char buf[64];

	snprintf(buf,sizeof(buf),"/sys/class/gpio/gpio%d/direction",gpio);
	fd = open(buf,O_WRONLY);
	if(fd<0){
		perror("gpio/drection");
		return fd;
	}
	if (dirStatus=="out")
		write(fd,"out",4);
	else
		write(fd,"in",3);
	close(fd);
	return 0;
}

int gpio_set_value(unsigned int gpio,int value){
	int fd;
	char buf[64];

	snprintf(buf,sizeof(buf),"/sys/class/gpio/gpio%d/value",gpio);
	fd = open(buf,O_WRONLY);
	if(fd<0){
		perror("gpio/set-value");
		return fd;
	}
	if (value == 0)
		write(fd,"0",2);
	else
		write(fd,"1",2);
	close(fd);
	return 0;
}
