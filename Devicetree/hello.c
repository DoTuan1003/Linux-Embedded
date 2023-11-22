#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
#include <linux/time.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/of.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/uaccess.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/mod_devicetable.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/device.h>
#include <linux/miscdevice.h>

struct timer_list my_timer;
unsigned int count = 0;
struct config data_global;
struct config
{
    char name[25]; //ten den
    unsigned int delay_time; //delay time
	unsigned int times; //delay time
    void __iomem *base_addr; //base address
    unsigned int data; //gia tri ghi vao thanh ghi dataout va clear data out
    unsigned int dataout;//gia tri ghi vao thanh ghi cau hinh io
	unsigned int dataclear;
};

static const struct of_device_id blink_led_of_match[] = {
	{ .compatible = "led-example0"},
	{},
};
static void timer_function(struct timer_list *t)
{
	if ((count % 2) == 0) {
		writel_relaxed(data_global.data,  data_global.base_addr + data_global.dataout);
		//pr_info("bat den\n");
		}
	else{
		writel_relaxed(data_global.data,  data_global.base_addr + data_global.dataclear);
		//pr_info("tat den\n");
		}
	count++;
    if (count < (data_global.times))
    {
        mod_timer(t, jiffies + HZ/(data_global.delay_time));
    }
    else {
        count=0;
    }
}
static int blink_led_probe(struct platform_device *pdev)
{
	struct resource *res = NULL;
	struct device_node *of_node = NULL;
    uint32_t output[5];
    uint32_t leg_config[2];
	uint32_t reg_data = 0;
    memset(output,0,sizeof(output));
	memset(leg_config,0,sizeof(leg_config));
    of_node=pdev->dev.of_node;
    
	of_property_read_u32_array(of_node, "led_regs", output, 5);
    of_property_read_u32_array(of_node, "led_config", leg_config, 2);
    
    pr_info("led_regs: %08x %08x %08x %08x %08x\n", output[0],
            output[1], output[2], output[3], output[4]);
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pr_info("reg: %016x %016x\n", res->start, res->end);


	data_global.base_addr = ioremap(res->start, (res->end - res->start) +0x1);
	pr_info("ioremap: %016x %016x\n", res->start,(res->end - res->start) +0x1);
	reg_data = readl_relaxed(data_global.base_addr + output[3]);
	pr_info("read xong\n");
	reg_data &= ~( output[0]);
	pr_info("regdata=%08x\n",reg_data);
	writel_relaxed(reg_data, data_global.base_addr + output[3]);
	pr_info("write xong\n");
	data_global.dataout=output[1];
	data_global.dataclear=output[2];
	data_global.data=output[0];
	data_global.delay_time=leg_config[1];
	pr_info("delaytime:%08x\n",leg_config[1]);
	data_global.times=leg_config[0];
	pr_info("times:%08x\n",leg_config[0]);

    timer_setup(&my_timer, timer_function, 0);
    add_timer(&my_timer);

    return 0;
}

static int blink_led_remove(struct platform_device *pdev)
{
	del_timer_sync(&my_timer);
	return 0;
}

static struct platform_driver blink_led_driver = {
	.probe		= blink_led_probe,
	.remove		= blink_led_remove,
	.driver		= {
		.name	= "blink_led",
		.of_match_table = blink_led_of_match,
	},
};

module_platform_driver(blink_led_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Do tuan");
MODULE_DESCRIPTION("Hello world kernel module");
