#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/jiffies.h>

#define PROC_FILENAME "jiffies"

static int proc_jiffies_show(struct seq_file *m, void *v) {
    seq_printf(m, "%lu\n", jiffies);
    return 0;
}

static int proc_jiffies_open(struct inode *inode, struct file *file) {
    return single_open(file, proc_jiffies_show, NULL);
}

static const struct proc_ops proc_jiffies_ops = {
    .proc_open = proc_jiffies_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init proc_jiffies_init(void) {
    proc_create(PROC_FILENAME, 0, NULL, &proc_jiffies_ops);
    return 0;
}

static void __exit proc_jiffies_exit(void) {
    remove_proc_entry(PROC_FILENAME, NULL);
}

module_init(proc_jiffies_init);
module_exit(proc_jiffies_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Chap2P1");
MODULE_DESCRIPTION("A kernel module that reports jiffies");
