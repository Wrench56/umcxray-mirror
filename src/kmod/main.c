#include <linux/init.h>
#include <linux/module.h>
#include <linux/err.h>

#include <linux/printk.h>
#include <linux/debugfs.h>

#include "umcxray.h"
#include "addr_resolver.h"

static struct debugfs_blob_wrapper regs_wrapper = (struct debugfs_blob_wrapper) {
    .data = NULL,
    .size = sizeof(struct umc_regs)
};

static struct umc_regs regs = { 0 };

static struct dentry *root = NULL;
static struct dentry *regfile = NULL;

static int __init init(void)
{
    pr_info("%s: loading...\n", KBUILD_MODNAME);

    void *test = kprobe_symbol_lookup("sys_do_open");
    if (test == NULL)
    {
        pr_err("%s: kprobe_symbol_lookup(): sys_do_open() not found!", KBUILD_MODNAME);
        return 1;
    }

    root = debugfs_create_dir("umcxray", NULL);
    if (IS_ERR(root))
    {
        long ec = PTR_ERR(root);
        pr_err("%s: debugfs_create_dir(): Fail with error %li!\n", KBUILD_MODNAME, ec);
        return ec;
    }

    regs.magic = UMC_MAGIC;
    /* TODO: Fill UMC register */

    regs_wrapper.data = &regs;

    regfile = debugfs_create_blob("regs", 0, root, &regs_wrapper);
    if (IS_ERR(regfile))
    {
        long ec = PTR_ERR(regfile);
        pr_err("%s: debugfs_create_blob(): Fail with error %li!\n", KBUILD_MODNAME, ec);
        debugfs_remove(root);
        return ec;
    }

    pr_info("%s: loaded!\n", KBUILD_MODNAME);
    return 0;
}

static void __exit cleanup(void)
{
    pr_info("%s: unloading...\n", KBUILD_MODNAME);

    if (regfile != NULL)
    {
        debugfs_remove(regfile);
    }

    if (root != NULL)
    {
        debugfs_remove(root);
    }

    pr_info("%s: unloaded!\n", KBUILD_MODNAME);
}

module_init(init);
module_exit(cleanup);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("arch.fail");
MODULE_DESCRIPTION("Expose the registers of the Zen UMC AMD64 interface");
MODULE_VERSION("0.0.1");
