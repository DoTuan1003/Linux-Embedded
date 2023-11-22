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

#define GPIO_ADDR_BASE 0x44E07000
#define ADDR_SIZE (0x1000)
#define GPIO_SETDATAOUT_OFFSET 0x194
#define GPIO_CLEARDATAOUT_OFFSET 0x190
#define GPIO_OE_OFFSET 0x134
#define LED ~(1 << 31)
#define DATA_OUT (1 << 31)

#define GPIO_20 (20)

void __iomem *base_addr;
unsigned int count = 0;

struct timer_list my_timer;

// Ham xu ly timer
static void timer_function(struct timer_list *t)
{
	if ((count % 2) == 0) 
		writel_relaxed(DATA_OUT,  base_addr + GPIO_SETDATAOUT_OFFSET);
	else
		writel_relaxed(DATA_OUT, base_addr + GPIO_CLEARDATAOUT_OFFSET); 

	count++;
	mod_timer(&my_timer, jiffies + HZ);
}

int init_module(void)
{
    uint32_t reg_data = 0;

    pr_info("Hello world driver is loaded\n");

    base_addr = ioremap(GPIO_ADDR_BASE, ADDR_SIZE);
    reg_data = readl_relaxed(base_addr + GPIO_OE_OFFSET);
    reg_data &= LED;
    writel_relaxed(reg_data, base_addr + GPIO_OE_OFFSET);

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
MODULE_AUTHOR("Do huu tuan");
MODULE_DESCRIPTION("GPIO led kernel module");