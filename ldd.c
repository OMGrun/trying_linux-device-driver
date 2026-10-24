#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saint");
MODULE_DESCRIPTION("Our first dynamically loadable kernel module");

static int saint_module_init (void) {
	printk("Hello, again! (from Saint!!)\n");
	return 0;
}

static void saint_module_exit (void) {
	printk("Good, Bye! (from Saint!!)\n");
}

module_init(saint_module_init);
module_exit(saint_module_exit);

