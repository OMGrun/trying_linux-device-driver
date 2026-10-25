#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saint");
MODULE_DESCRIPTION("Our first dynamically loadable kernel module");

static struct proc_dir_entry *proc_entry;
struct proc_ops driver_proc_ops = {

};

static int saint_module_init (void) {
	printk("saint_module_init: entry\n");
	proc_entry = proc_create(
			"saint_driver", 
			0, 
			NULL, 
			&driver_proc_ops);
	printk("saint_module_init: exit\n");

	return 0;
}

static void saint_module_exit (void) {
	printk("saint_module_exit: entry\n");
	proc_remove(proc_entry);
	printk("saint_module_exit: exit\n");
}


module_init(saint_module_init);
module_exit(saint_module_exit);
