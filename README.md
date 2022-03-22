# Linux loadable kernel module(LKM)
A loadable kernel module (LKM) is a mechanism for adding/removing code from Linux kernel at run time. Many of device drivers are implemented through this way, otherwise the monolithic kernel would be too large.

LKM communicates with user-space applications through system calls, and it can access almost all the objects/services of the kernel. LKM can be inserted to the monolithic kernel at any time – usually at booting or running phase.

Writing LKM has many advantages against directly tweaking the whole kernel. For LKM can be dynamically inserted or removed at run time, we don’t need to recompile the whole kernel nor reboot, and it’s more shippable.

So, the easiest way to start kernel programming is to write a module - a piece of code that can be dynamically loaded into the kernel.

### Installing the Development Environment
we need to run:
```
apt-get install build-essential linux-headers-`uname -r`
```

### Testing Our Example
Let’s modify our Makefile to only load the module and not unload it.
```Makefile
obj-m += lkm_example.o
all:
  make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
  make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
test:
  # We put a — in front of the rmmod command to tell make to ignore
  # an error in case the module isn’t loaded.
  -sudo rmmod lkm_example
  # Clear the kernel log without echo
  sudo dmesg -C
  # Insert the module
  sudo insmod lkm_example.ko
  # Display the kernel log
  dmesg
```

Take the value you obtain from “make test” and use it to create a device file so that we can communicate with our kernel module from user space.
```
sudo mknod /dev/lkm_example c MAJOR 0
```

The “c” in the mknod command tells mknod that we need a character device file created. Now we can grab content from the device:
```
cat /dev/lkm_example
```

or even via the “dd” command:
```
dd if=/dev/lkm_example of=test bs=14 count=100
```

You can also access this device via applications. They don’t have to be compiled applications — even Python, Ruby, and PHP scripts can access this data.
When we’re done with the device, delete it and unload the module:
```
sudo rm /dev/lkm_example
```
```
sudo rmmod lkm_example
```

(in the above example, replace MAJOR with the value you obtain from “make test” or “dmesg”)

Now we can insert the module to test it. To do this, run:
```bash
sudo insmod lkm_example.ko
```

The printk function doesn’t output to the console but rather the kernel log. To see that, we’ll need to run:
```
sudo dmesg
```

You should see the “Hello, World!” line prefixed by a timestamp. This means our kernel module loaded and successfully printed to the kernel log. We can also check to see if the module is still loaded:
```
lsmod | grep “lkm_example”
```

To remove the module, run:
```
sudo rmmod lkm_example
```

