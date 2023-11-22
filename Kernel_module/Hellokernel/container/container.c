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
#define LED31 ~(1 << 31)
#define DATA_OUT31 (1 << 31)

#define LED30 ~(1 << 30)
#define DATA_OUT30 (1 << 30)

struct container *container1 = NULL;
struct container *container2 = NULL;

struct container
{
    char name[25]; //ten den
    int delay_time; //delay time
    void __iomem *base_addr; //base address
    unsigned int data; //gia tri ghi vao thanh ghi dataout va clear data out
    unsigned int setupio;//gia tri ghi vao thanh ghi cau hinh io
    unsigned int count;
    struct timer_list my_timer;
};

// Ham xu ly timer
static void timer_function(struct timer_list *t)
{

    struct container *container_ptr = container_of(t, struct container, my_timer);
	if ((container_ptr->count % 2) == 0) 
		writel_relaxed(container_ptr->data,  container_ptr->base_addr + GPIO_SETDATAOUT_OFFSET);
	else
		writel_relaxed(container_ptr->data, container_ptr->base_addr + GPIO_CLEARDATAOUT_OFFSET); 

	container_ptr->count++;
	mod_timer(&container_ptr->my_timer, jiffies + HZ/container_ptr->delay_time);
}

int init_module(void)
{
    uint32_t reg_data = 0;

    pr_info("Hello world driver is loaded\n");
    container1 = kmalloc(sizeof(struct container), GFP_KERNEL);
    container2 = kmalloc(sizeof(struct container), GFP_KERNEL);

    container1->delay_time = 5;
    container1->data = DATA_OUT31;
    container1->setupio=LED31;
    container1->base_addr = ioremap(GPIO_ADDR_BASE, ADDR_SIZE);
    container1->count=0;

    reg_data = readl_relaxed(container1->base_addr + GPIO_OE_OFFSET);
    reg_data &= container1->setupio;
    writel_relaxed(reg_data, container1->base_addr + GPIO_OE_OFFSET);

    timer_setup(&container1->my_timer, timer_function, 0);
    add_timer(&container1->my_timer);
    //DEN2
    container2->delay_time = 10;
    container2->data = DATA_OUT30;
    container2->setupio=LED30;
    container2->base_addr = ioremap(GPIO_ADDR_BASE, ADDR_SIZE);
    container2->count=0;

    reg_data = readl_relaxed(container2->base_addr + GPIO_OE_OFFSET);
    reg_data &= container2->setupio;
    writel_relaxed(reg_data, container2->base_addr + GPIO_OE_OFFSET);

    timer_setup(&container2->my_timer, timer_function, 0);
    add_timer(&container2->my_timer);

    return 0;
}

void cleanup_module(void)
{
    del_timer_sync(&container1->my_timer);
    del_timer_sync(&container2->my_timer);
    kfree(container1);
    kfree(container2);
    pr_info("hello world driver is unloaded\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Do huu tuan");
MODULE_DESCRIPTION("GPIO led kernel module");