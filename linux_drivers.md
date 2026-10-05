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

.ko files are what the kernel takes, and then we need to check if it verifies and the way to check if verifies is to call a util called insmod: hence, sudo insmod ldd.ko then check with echo $? and if 0 then good!

for example in our code, we have:
the printk which we expect to show the print message in the kernel logs, so how do we see the kernal logs? sudo dmesg. We expect to now see the hello world from the initialisation!

So now, how do we remove the modules? `sudo rmmod ldd` and then if you sudo dmesg then it should print
goodybye or anythign our message says

So bascially, our saint-module-init is the constructor and saint-module-exit is the destructor
