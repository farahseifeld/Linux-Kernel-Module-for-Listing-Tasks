/**
 * listDFS.c
 *
 * A kernel module for listing tasks using depth first search. 
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hash.h>
#include <linux/gcd.h>
#include <asm/param.h>
#include <linux/sched.h>


/* This function is called when we want to list tasks using depth first search. */
void DFS(struct task_struct *head)
{
	struct task_struct *task;
	struct list_head *list;

	//printing command name, state, and pid of the parent (current) task
	printk(KERN_INFO "Command:%-22s\t State:%ld\t PID:%d\n ",head->comm,head->state, head->pid);

	
	//getting the children of the head
	list_for_each(list, &head->children)
	{
		//getting the sibling of the child of the current node
		task=list_entry(list, struct task_struct, sibling);
	
		//recursive call with the sibling
		DFS(task);
	}

}

/* This function is called when the module is loaded. */
int simple_init(void)
{
	printk(KERN_INFO "Loading Listing Tasks DFS Module\n");
	
	//listing tasks using depth first search
	DFS(&init_task);

       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {

	printk(KERN_INFO "Removing Listing Tasks DFS Module\n");

}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Listing Tasks DFS Module");
MODULE_AUTHOR("SGG");

