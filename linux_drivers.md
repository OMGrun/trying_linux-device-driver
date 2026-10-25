# My notes
A multipass is basically a hypervisor or instance manager and then we can ssh from vscod.
Remember the way to connect is is basically by going into vscodium ssh target config:

Host github.com
    AddKeyToAgent
    UseKeychain
    IdentifyFile (where your key lives)

Host primary (for the multipass)
    HostName (the address)
    User (username, in this case, ubuntu)
    IndetityFile (where your key lives)
    IdentitiesOnly

# Getting Started on simply printing an output in the kernel
.ko files are what the kernel takes, and then we need to check if it verifies and the way to check if verifies is to call a util called insmod: hence, sudo insmod ldd.ko then check with echo $? and if 0 then good!

for example in our code, we have:
the printk which we expect to show the print message in the kernel logs, so how do we see the kernal logs? sudo dmesg. We expect to now see the hello world from the initialisation!

So now, how do we remove the modules? `sudo rmmod ldd` and then if you sudo dmesg then it should print
goodybye or anythign our message says

so, for step by step

```bash
make # you will haver the ldd.ko make clean to clear up the files
sudo insmod ldd.ko # feed into the kernel/load module into the kernel
echo $? #if it prints 0, it is a success
sudo dmesg #log buffer to see if our instruction was printed, you should see hello world on the very last line (prints kernel log)
sudo rmmod ldd # to unplug from kernel.

```

for refernece, this is the C-code:

```c
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Saint");
MODULE_DESCRIPTION("Our first dynamically loadable kernel module");

static int saint_module_init (void) {
	printk("Hello, World! (from Saint!!)\n");
	return 0;
}

static void saint_module_exit (void) {
	printk("Good, Bye! (from Saint!!)\n");
}

module_init(saint_module_init);
module_exit(saint_module_exit);
```
take a look at module\_init and exit, they are what you call macros and comes from the header file

why is GPL necessary, it gives you access to things in the lincese, such that it does not restrict you.

```bash

sudo dmesg -c # prints kernel log and also clears it!

```
if you do `modinfo` it prints the info, ie the file name, description, author, lincese, etc.
It does not need the file name, just the access to the .ko file is good

This right here is the bare minimum code that we need to write a linux kernel module

---

## Deep dive into Makefile and the basics of MakeFile (good to know)

make is a utility which helps with automation (kinda like bash i guess?), for executing commands that we can write on the shell

ie, `gcc main.c -o main` we can make make (pun intended) execute the command for us.
Very important: The makefile file name has to be Makefile, the M must be capital or you can do filename.mk
but then you have to flag the make file, ie, `make -f ---.mk target`

Now *syntax and rules*

we specify:

target: dependencies (first line is dependencies)
    gcc main.c ... (tab command, must have tab)

then you can haver another taget and so on and so forth, targets don't always need to have a dependency

target name can be anything, for example, we want x.c $\rarr$ x.o

then
```mk
xyz: x.c
    gcc x.c -o x.o
```

you can write, make xyz, then it will find the target called xyz, and check "do we have the x.c file. yes? then it will execute the gcc command.

The first time it is executed, it will check if the output exists, the second time we run it, it will compare the time and x.o is newer than x.c then it will not run the command, it will run the command if x.o is older though.

It has to be a tab under the target btw, cannot be spaces or anything, must be a tab character. If we just run make, it
will execute the first target, and then if you specify it then it will run the specificed target.

One concrete example, say you have a makefile called saint.mk and in there you have a test.text target, you can run that target by doing
`make -f saint.mk test.text`

---

## Exploring LSMOD

handy to ensure that our module is accepted by the kernel.

if forexample, you type out `lsmod` into the terminal, you will see all the modules that are loaded, as well as who is refering to it.

if you do `rmmod ldd` and then `lsmod` you will see that it is no longer in the list. This is exactly how you check!

## insmod module
1. calls `init_module` to hint the kernel that a module insertion is attempted.
2. Transfers control to the kernel
3. Kernel execute `sys_init_module`
4. verifies permissions
5. `load_module` funbction is called 
    1. checks the sanity of the .ko
    2. creates memory
    3. Copies from user space to kernel space
    4. Resolves sysbols.
    5. Returns a reference to the kernel
6. Adds the reference to a linked list that has all the loaded modules.
7 `module_init` listed function

## rmmod module
1. `rmmod` calls `delete_module()` which hints the kernel that a module is to be removed
    1. control is transfered to the kernel
2. Kernel executes `sys_delete_module()`
    1. Checks the permissions of the one requesting.
    2. Check if any other loaded module needs the current module.
    3. Checks if the module is actualyl loaded
    4. Executes the function provided in `module_exit`
    5. `free_module()`
        1. removes references and kernel object references
        2. performs any other cleanup.
        3. unloads the module
        4. changes the state in list
        5. removes it from the list and frees the memory

## modinfo

shows the infomration about the file, ie, the filename, description, author, license, etc


## making the driver interactive

we will go for a simpler file system called a proc file system (virtual file system)
/proc directory is not a real file, they are logical and imaginary. 

when a read write happens, the kernel dynamically print some output to the user

now we are going to implement the driver handling the read.

there is a kernel api available to create the proc file system entry

what is interesting is that when i do, `file /proc/driver/rtc` it is empty however, when i `cat` it prints. 
Most likely because there is an rtc driver there which detects the read() operation

so the files of the proc does not exist on the real disk but reading and printing it can lead to interesting results, the driverdynamically prints that information

so we use the `#include <linux/proc_fs.h>` to mess around with the proc file

so now, our new code looks like this

```c
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

```
now when we do insmod ldd.ko and then do lsmod you should see that it is loaded, then if you do `ls /proc/` you should see the file called "saint\_driver"



NOTE: Special thanks to inpyjamaarchieves and freeCodeCamp.org on YT as they were the one who taught this
