#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define DEVICE_NAME "ballmer"
#define CLASS_NAME "ballmer"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rachel Snijders");
MODULE_DESCRIPTION("Get inspired by our lord and savior, Steve Ballmer.");
MODULE_VERSION("0.1");

static int majorNumber;
static struct class* ballmerClass = NULL;
static struct cdev ballmer_cdev;

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    int errors = 0;
    char *message = "Developers, Developers, Developers\n";
    int message_len = strlen(message);

    errors = copy_to_user(buffer, message, message_len);

    return errors == 0 ? message_len : -EFAULT;
}

static struct file_operations dev_fops = {
   .owner = THIS_MODULE,
   .read = dev_read,
};

static int __init ballmer_init(void) {
   majorNumber = register_chrdev(0, DEVICE_NAME, &dev_fops);
   if (majorNumber<0){
      return majorNumber;
   }
   ballmerClass = class_create(THIS_MODULE, CLASS_NAME);
   if (IS_ERR(ballmerClass)){
      unregister_chrdev(majorNumber, DEVICE_NAME);
      return PTR_ERR(ballmerClass);
   }
   if (!device_create(ballmerClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME)){
      class_destroy(ballmerClass);
      unregister_chrdev(majorNumber, DEVICE_NAME);
      return -1;
   }
   cdev_init(&ballmer_cdev, &dev_fops);
   if (cdev_add(&ballmer_cdev, MKDEV(majorNumber, 0), 1) == -1) {
      device_destroy(ballmerClass, MKDEV(majorNumber, 0));
      class_destroy(ballmerClass);
      unregister_chrdev(majorNumber, DEVICE_NAME);
      return -1;
   }
   printk(KERN_INFO "Ballmer module loaded.\n");
   return 0;
}

static void __exit ballmer_exit(void) {
   device_destroy(ballmerClass, MKDEV(majorNumber, 0));
   class_destroy(ballmerClass);
   unregister_chrdev(majorNumber, DEVICE_NAME);
   printk(KERN_INFO "Ballmer module removed.\n");
}

module_init(ballmer_init);
module_exit(ballmer_exit);

