#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/time.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/timer.h>
#include <linux/slab.h>
#include <linux/gpio.h>

void my_gpio_setvalue(unsigned int gpio_num, unsigned int val)
{
    pr_info("set %u for gpio number %u\n", val, gpio_num);
    gpio_set_value(gpio_num, val);
}
EXPORT_SYMBOL(my_gpio_setvalue);

int init_module(void)
{
    pr_info("Hello world driver is loaded\n");

    return 0;
}

void cleanup_module(void)
{
    pr_info("hello world driver is unloaded\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ta Manh Tuyen");
MODULE_DESCRIPTION("GPIO led kernel module");