#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>

#define PROC_FILENAME "pid"

static int pid_value = 0;

static ssize_t procfs_read(struct file *file, char __user *buffer, size_t length, loff_t *offset) {
    struct task_struct *task;
    char buf[256];
    int len = 0;

    if (*offset > 0)
        return 0; // EOF

    task = pid_task(find_vpid(pid_value), PIDTYPE_PID);
    if (task != NULL) {
        len = snprintf(buf, sizeof(buf), "command = [%s] pid = [%d] state = [%c]\n",
                       task->comm, task->pid, task_state_to_char(task));
        if (len > length)
            len = length;
        if (copy_to_user(buffer, buf, len) != 0) {
            return -EFAULT;
        }
        *offset += len;
        return len;
    } else {
        return -ESRCH; // No such process
    }
}

static ssize_t procfs_write(struct file *file, const char __user *buffer, size_t length, loff_t *offset) {
    char buf[16];
    int ret;

    if (length > sizeof(buf) - 1)
        return -EINVAL;

    if (copy_from_user(buf, buffer, length))
        return -EFAULT;

    buf[length] = '\0';
    ret = kstrtoint(buf, 10, &pid_value);
    if (ret != 0)
        return ret;

    return length;
}

static const struct proc_ops proc_fops = {
    .proc_read = procfs_read,
    .proc_write = procfs_write,
};

static int __init procfs_example_init(void) {
    if (!proc_create(PROC_FILENAME, 0666, NULL, &proc_fops)) {
        printk(KERN_ERR "Failed to create /proc/%s\n", PROC_FILENAME);
        return -ENOMEM;
    }
    printk(KERN_INFO "/proc/%s created\n", PROC_FILENAME);
    return 0;
}

static void __exit procfs_example_exit(void) {
    remove_proc_entry(PROC_FILENAME, NULL);
    printk(KERN_INFO "/proc/%s removed\n", PROC_FILENAME);
}

module_init(procfs_example_init);
module_exit(procfs_example_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple /proc example module");

