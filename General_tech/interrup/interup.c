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
#include <linux/interrupt.h>

#define GPIO0_20 (20)
#define GPIO0_31 (31)
#define BUTTON_DEV "example_of_irq"

int irq = -1;

static irqreturn_t button_isr(int irq, void *data)
{
    static int count;

    if (count % 2 == 0)
        gpio_set_value(GPIO0_20, 1);
    else
        gpio_set_value(GPIO0_20, 0);

    count++;

    return IRQ_HANDLED;
}

int init_module(void)
{
    int ret=-1;
    uint32_t val=0;
    pr_info("Hello world driver is loaded\n");

    if (gpio_is_valid(GPIO0_20) == false)
    {
        pr_err("GPIO %d is not valid\n", GPIO0_20);
        return -1;
    }

    gpio_request(GPIO0_20,"GPIO0_20");
    gpio_request(GPIO0_31,"GPIO0_31");

    gpio_direction_output(GPIO0_20, 0);
    val=gpio_get_value(GPIO0_31);
    printk("thanh gi 31: %08x\n",val);
    irq=gpio_to_irq(GPIO0_31);
    
    ret= request_irq(irq ,button_isr,IRQF_TRIGGER_RISING,"my_interrupt_handler", BUTTON_DEV);
    return 0;
}

void cleanup_module(void)
{
    pr_info("hello world driver is unloaded\n");
    gpio_set_value(GPIO0_20, 0);
    free_irq(irq, BUTTON_DEV);
    gpio_free(GPIO0_20);
    gpio_free(GPIO0_31);
    pr_info("hello world driver is unloaded\n");
}

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("GPIO led kernel module");