#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/jiffies.h>

#define PROC_FILENAME "seconds"

static unsigned long start_jiffies;

static int seconds_proc_show(struct seq_file *m, void *v) {
    unsigned long elapsed_jiffies = jiffies - start_jiffies;
    unsigned long elapsed_seconds = elapsed_jiffies / HZ;
    seq_printf(m, "%lu\n", elapsed_seconds);
    return 0;
}

static int seconds_proc_open(struct inode *inode, struct file *file) {
    return single_open(file, seconds_proc_show, NULL);
}

static const struct proc_ops seconds_proc_ops = {
    .proc_open = seconds_proc_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init seconds_module_init(void) {
    start_jiffies = jiffies;
    proc_create(PROC_FILENAME, 0, NULL, &seconds_proc_ops);
    return 0;
}

static void __exit seconds_module_exit(void) {
    remove_proc_entry(PROC_FILENAME, NULL);
}

module_init(seconds_module_init);
module_exit(seconds_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chap2P1");
MODULE_DESCRIPTION("A kernel module that reports elapsed seconds");
