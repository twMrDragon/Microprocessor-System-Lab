#ifndef GPIO_H
#define GPIO_H
#include <string>

class GPIO
{
public:
    GPIO();
    static int gpio_export(unsigned int gpio);
    static int gpio_unexport(unsigned int gpio);
    static int gpio_set_dir(unsigned int gpio,std::string dirStatus);
    static int gpio_set_value(unsigned int gpio,int value);
};

#endif // GPIO_H
