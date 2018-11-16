/**
 * list.c
 *
 * A kernel module for listing tasks linearly. 
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <asm/param.h>
#include <linux/sched.h>

struct task_struct *task;

/* This function is called when the module is loaded. */
int simple_init(void)
{
	printk(KERN_INFO "Loading Listing Tasks Linearly Module\n");
	
	//iterating over tasks linearly	
	for_each_process(task)
	{
		//printing command name of tasks, its state, and its pid.
		printk(KERN_INFO "Command:%-22s\t State:%ld\t PID:%d\n ",task->comm,task->state, task->pid);
	}

       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {

	printk(KERN_INFO "Removing Listing Tasks Linearly Module\n");

}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Listing Tasks Linear Module");
MODULE_AUTHOR("SGG");

