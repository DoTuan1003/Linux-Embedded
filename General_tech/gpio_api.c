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

#define GPIO_20 (20)


struct timer_list my_timer;
void my_gpio_setvalue(unsigned int gpio_num, unsigned int val);

// Ham xu ly timer
static void timer_function(struct timer_list *t)
{
    int i = 0;

    for (i = 10; i > 0; i--) {
        my_gpio_setvalue(GPIO_20, 1);
        msleep(1000);
        my_gpio_setvalue(GPIO_20, 0);
        msleep(1000);
    }
}

int init_module(void)
{
    pr_info("Hello world driver is loaded\n");

    if (gpio_is_valid(GPIO_20) == false)
    {
        pr_err("GPIO %d is not valid\n", GPIO_20);
        return -1;
    }

    if(gpio_request(GPIO_20,"GPIO_20") < 0) {
        pr_err("ERROR: GPIO %d request\n", GPIO_20);
        return -1;
    }

    gpio_direction_output(GPIO_20, 0);
    gpio_export(GPIO_20, false);

    timer_setup(&my_timer, timer_function, 0);
    add_timer(&my_timer);

    return 0;
}

void cleanup_module(void)
{
    del_timer_sync(&my_timer);
    pr_info("hello world driver is unloaded\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ta Manh Tuyen");
MODULE_DESCRIPTION("GPIO led kernel module");