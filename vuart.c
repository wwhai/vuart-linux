#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
//--------------------------------------------------------
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("wwhai");
MODULE_DESCRIPTION("A simple virtual uart module");
MODULE_ALIAS("vuart");
MODULE_VERSION("V1.0.0");
//--------------------------------------------------------

#define MAJOR_NUM 257

static ssize_t vuart_read(struct file *, char *, size_t, loff_t *);
static ssize_t vuart_write(struct file *, const char *, size_t, loff_t *);
static long vuart_ioctl(struct file *, unsigned int, unsigned long);
// 初始化字符设备驱动的file_operations结构体
struct file_operations vuart_fops = {
    owner : THIS_MODULE,
    read : vuart_read,
    write : vuart_write,
    unlocked_ioctl : vuart_ioctl
};
//
static char *read_info = "GOODISDOG";

static int __init vuart_init(void)
{
    int ret = register_chrdev(MAJOR_NUM, "vuart", &vuart_fops);
    if (ret == 0)
    {
        printk(KERN_INFO "vuart register success");
    }
    else
    {
        printk(KERN_INFO "vuart register failed: %d", ret);
    }
    return ret;
}

static void __exit vuart_exit(void)
{
    unregister_chrdev(MAJOR_NUM, "vuart");
    printk(KERN_INFO "vuart unregister success");
}

static long vuart_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
    printk(KERN_INFO "vuart ioctl: %d %ld\n", cmd, arg);
    return 0;
}
static ssize_t vuart_read(struct file *filp, char *ubuf, size_t len, loff_t *off)
{
    if (copy_to_user(ubuf, read_info, 9))
    {
        return -EFAULT;
    }
    return 9;
}

static ssize_t vuart_write(struct file *filp, const char *ubuf, size_t len, loff_t *off)
{
    printk(KERN_INFO "vuart_write:%s\n", ubuf);
    return sizeof(int);
}

module_init(vuart_init);
module_exit(vuart_exit);