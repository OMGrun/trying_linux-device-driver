#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saint");
MODULE_DESCRIPTION("Our first dynamically loadable kernel module");

static struct proc_dir_entry *proc_entry;



static ssize_t saint_read(struct file * file_pointer, char __user *user_space_buffer, size_t count, loff_t * offset) {
	char msg[] = "Ack!\n";
	size_t len = strlen(msg);
	int result;


	result = copy_to_user(user_space_buffer, msg, len);
	



	printk("saint_read\n");
	return len;
}



struct proc_ops driver_proc_ops = {

	.proc_read = saint_read

};

static int saint_module_init (void) {
	printk("saint_module_init: entry\n");

	proc_entry = proc_create(
			"saint_driver", 
			0, 
			NULL, 
			&driver_proc_ops);

	if (proc_entry == NULL) {
		printk("saint_module_init: error\n");
		return -1;
	}

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
