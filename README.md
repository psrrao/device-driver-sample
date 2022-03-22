# Linux loadable kernel module(LKM)
A loadable kernel module (LKM) is a mechanism for adding/removing code from Linux kernel at run time. Many of device drivers are implemented through this way, otherwise the monolithic kernel would be too large.

LKM communicates with user-space applications through system calls, and it can access almost all the objects/services of the kernel. LKM can be inserted to the monolithic kernel at any time – usually at booting or running phase.

Writing LKM has many advantages against directly tweaking the whole kernel. For LKM can be dynamically inserted or removed at run time, we don’t need to recompile the whole kernel nor reboot, and it’s more shippable.

So, the easiest way to start kernel programming is to write a module - a piece of code that can be dynamically loaded into the kernel.
