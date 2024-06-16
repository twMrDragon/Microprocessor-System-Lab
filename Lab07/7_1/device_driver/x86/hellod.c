#include <linux/kernel.h>
#include <linux/module.h>

static int __init tx2_hello_module_init(void){
    printk("Hello, x86 module is installed !\n");
    return 0;
}

static void __exit tx2_hello_module_cleanup(void){
    printk("Good-bye, x86 module was removed!\n");
}

module_init(tx2_hello_module_init);
module_exit(tx2_hello_module_cleanup);
MODULE_LICENSE("GPL");