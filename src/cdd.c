#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include <linux/timer.h>

#define DEVICE_NAME "gpio_driver_test"
#define CLASS_NAME "gpio_test"
#define GPIO_PIN1 20
#define GPIO_PIN2 21
#define TIMER_INTERVAL HZ  // 1 second

static int major_number;
static struct class* cl = NULL;

static struct timer_list my_timer;

static int selected_signal = 1; // 1 for GPIO_PIN1, 2 for GPIO_PIN2
static int gpio_value = 0;

static void read_gpio_values(struct timer_list* timer) {
    if (selected_signal == 1) {
        gpio_value = gpio_get_value(GPIO_PIN1);
    } else {
        gpio_value = gpio_get_value(GPIO_PIN2);
    }
    mod_timer(&my_timer, jiffies + TIMER_INTERVAL);
}

static int dev_open(struct inode *i, struct file *f)
{
    printk(KERN_INFO "GPIO Driver: open()\n");
    return 0;
}

static int dev_close(struct inode *i, struct file *f)
{
    printk(KERN_INFO "GPIO Driver: close()\n");
    return 0;
}

static ssize_t dev_read(struct file* filep, char* buffer, size_t len, loff_t* offset) {
    char msg[256];
    int msg_len;

    msg_len = snprintf(msg, sizeof(msg), "Signal: %d\n", gpio_value);
    if (*offset >= msg_len) {
        return 0;
    }

    if (len > msg_len - *offset) {
        len = msg_len - *offset;
    }

    if (copy_to_user(buffer, msg + *offset, len) != 0) {
        return -EFAULT;
    }

    *offset += len;
    return len;
}

static ssize_t dev_write(struct file* filep, const char* buffer, size_t len, loff_t* offset) {
    char msg[256];

    if (len > sizeof(msg) - 1) {
        len = sizeof(msg) - 1;
    }

    if (copy_from_user(msg, buffer, len) != 0) {
        return -EFAULT;
    }

    msg[len] = '\0';
    if(kstrtoint(msg, 10, &selected_signal) != 0)
    {
        return -EFAULT;
    }
    return len;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = dev_open,
    .release = dev_close,
    .read = dev_read,
    .write = dev_write,
};

static int __init gpio_init(void) {
    
    struct device* dev_ret = NULL;
    printk(KERN_INFO "GPIO Driver: Initializing the GPIO Driver\n");

    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "GPIO Driver: Failed to register a major number\n");
        return major_number;
    }
    printk(KERN_INFO "GPIO Driver: Registered with major number %d\n", major_number);

    cl = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(cl)) {
        unregister_chrdev(major_number, DEVICE_NAME);
        printk(KERN_ALERT "Failed to register device class\n");
        return PTR_ERR(cl);
    }
    printk(KERN_INFO "GPIO Driver: Device class registered correctly\n");

    dev_ret = device_create(cl, NULL, MKDEV(major_number, 0), NULL, DEVICE_NAME);
    if (IS_ERR(dev_ret)) {
        class_destroy(cl);
        unregister_chrdev(major_number, DEVICE_NAME);
        printk(KERN_ALERT "Failed to create the device\n");
        return PTR_ERR(dev_ret);
    }
    printk(KERN_INFO "GPIO Driver: Device class created correctly\n");

    gpio_request(GPIO_PIN1, "GPIO_PIN1");
    gpio_direction_input(GPIO_PIN1);
    gpio_request(GPIO_PIN2, "GPIO_PIN2");
    gpio_direction_input(GPIO_PIN2);

    timer_setup(&my_timer, read_gpio_values, 0);
    mod_timer(&my_timer, jiffies + TIMER_INTERVAL);

    printk(KERN_INFO "GPIO Driver: GPIOs initialized and timer set up\n");
    return 0;
}

static void __exit gpio_exit(void) {
    printk(KERN_INFO "GPIO Driver: Exiting the GPIO Driver\n");

    del_timer(&my_timer);
    gpio_free(GPIO_PIN1);
    gpio_free(GPIO_PIN2);

    device_destroy(cl, MKDEV(major_number, 0));
    class_unregister(cl);
    class_destroy(cl);
    unregister_chrdev(major_number, DEVICE_NAME);

    printk(KERN_INFO "GPIO Driver: Goodbye from the GPIO Driver\n");
}


module_init(gpio_init);
module_exit(gpio_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Pary Joaquin, Colque Santiago and Angeloff Jorge");
MODULE_DESCRIPTION("A simple Linux GPIO driver for Raspberry Pi");
MODULE_VERSION("1.0");
