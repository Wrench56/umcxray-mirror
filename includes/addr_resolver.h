#ifndef ADDR_RESOLVER_H
#define ADDR_RESOLVER_H

#include <linux/kprobes.h>

void *kprobe_symbol_lookup(char *symbol_name);

#endif // ADDR_RESOLVER_H
