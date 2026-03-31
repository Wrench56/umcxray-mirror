#include <linux/printk.h>

#include "addr_resolver.h"

void *kprobe_symbol_lookup(char *symbol_name)
{
	void *kprobe_resolved_addr = NULL;
    static struct kprobe kp = { 0 };

    kp.symbol_name = symbol_name;

	register_kprobe(&kp);
	kprobe_resolved_addr = (void*) kp.addr;
	unregister_kprobe(&kp);

    pr_info("%s: kprobe addr = %px\n", KBUILD_MODNAME, kp.addr);

	return kprobe_resolved_addr;
}
