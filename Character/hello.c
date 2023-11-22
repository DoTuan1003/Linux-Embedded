#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/timer.h>


#define GPIO_ADDR_BASE 0x44E07000
#define ADDR_SIZE (0x1000)
#define GPIO_SETDATAOUT_OFFSET 0x194
#define GPIO_CLEARDATAOUT_OFFSET 0x190
#define GPIO_OE_OFFSET 0x134
#define LED ~(1 << 31)
#define DATA_OUT (1 << 31)
#define GPIO_DATAOUT 0x13C

void __iomem *base_addr;
struct config data_global;
struct timer_list my_timer;

struct config
{
    int times;
    int tanso;
};

static void timer_function(struct timer_list *t)
{
    static int count = 0;
    if (count % 2 == 0)
        writel_relaxed(DATA_OUT, base_addr + GPIO_SETDATAOUT_OFFSET);
    else
        writel_relaxed(DATA_OUT, base_addr + GPIO_CLEARDATAOUT_OFFSET);
    count++;
    pr_info("delay times: %d\n",count);
    if (count < (data_global.times))
    {
        mod_timer(t, jiffies + HZ/(data_global.tanso));
    }
    else {
        count=0;
    }
}
int misc_open(struct inode *node, struct file *filep)
{
    uint32_t reg_data = 0;
    pr_info("%s, %d\n", __func__, __LINE__);
    reg_data = readl_relaxed(base_addr + GPIO_OE_OFFSET);
    reg_data &= LED;
    writel_relaxed(reg_data, base_addr + GPIO_OE_OFFSET);
    return 0;
}

int misc_release(struct inode *node, struct file *filep)
{
    pr_info("%s, %d\n", __func__, __LINE__);

    return 0;
}

static ssize_t misc_read(struct file *filp, char __user *buf, size_t count,
                         loff_t *f_pos)
{   

    uint32_t reg_data=0;
    char status=0;
    int ret=0;

    reg_data = readl_relaxed(base_addr + GPIO_DATAOUT);
    reg_data = (reg_data>>31)&1;
    
    if(reg_data == 0){
        status='0';
    }
    else
        status='1';
    ret=copy_to_user(buf,&status,1);
    pr_info("%s, %d\n", __func__, __LINE__);
    return 0;
}
static ssize_t misc_write(struct file *filp, const char __user *buf,
                          size_t count, loff_t *f_pos)
{
    char local_data[128];
    int rets=0;
    memset(local_data,0,sizeof(local_data));
    rets=copy_from_user(local_data,buf,count < 128 ? count : 128);
    pr_info("%s, %d,chuoi str la:%s\n", __func__, __LINE__,local_data);
    switch(local_data[0])
    {
        case '1':
            //writel_relaxed(DATA_OUT,  base_addr + GPIO_SETDATAOUT_OFFSET);
            timer_setup(&my_timer, timer_function, 0);
            add_timer(&my_timer);
            break;
        case '2':
            writel_relaxed(DATA_OUT, base_addr + GPIO_CLEARDATAOUT_OFFSET); 
            break;
        default:
            pr_info("send invalid  commad\n");
            break;
    }
    return count;
}
#define MAGIC_NO	100
#define SEND_DATA_CMD	_IOW(MAGIC_NO, sizeof(struct config), struct config *)
#define GET_DATA_CMD	_IOR(MAGIC_NO, sizeof(struct config), struct config *)

static long misc_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
    int ret=0;
    struct config local_data;
    switch(cmd)
    {
        case SEND_DATA_CMD:
            ret=copy_from_user(&local_data,(struct config *) arg , sizeof(struct config));
            data_global.times=local_data.times;
            data_global.tanso=local_data.tanso;
            pr_info("%s, %d,time:%d,tanso:%d\n", __func__, __LINE__,local_data.times,local_data.tanso);
            break;
        case GET_DATA_CMD:
            ret=copy_to_user((struct config *) arg ,&data_global, sizeof(struct config));
            break;
        default:
            pr_info("invalid command\n");
            break;
    }
    

    return 0;
}

struct file_operations misc_fops = {
    .owner = THIS_MODULE,
    .open = misc_open, //Enable hardware
    .release = misc_release, //disable hardware, synchronize data xuong hardware
    .read = misc_read, //Doc du lieu tu hardware, luu vao buffer cua kernel
    .write = misc_write, //Ghi du lieu tu buffer cua kernel xuong hardware
    .unlocked_ioctl = misc_ioctl, //Chua cau hinh ve thoi gian sang cua den
};

static struct miscdevice misc_example = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "misc_example",
    .fops = &misc_fops,
    .mode= 0666,
};

static int misc_init(void)
{
    pr_info("misc module init\n");
    misc_register(&misc_example);
    base_addr = ioremap(GPIO_ADDR_BASE, ADDR_SIZE);

    return 0;
}

static void misc_exit(void)
{
    pr_info("misc module exit\n");
    misc_deregister(&misc_example);
    del_timer_sync(&my_timer);
}

module_init(misc_init);
module_exit(misc_exit);

MODULE_AUTHOR("Tuan");
MODULE_DESCRIPTION("Example misc driver.");
MODULE_LICENSE("GPL");