#include <sys/modctl.h>

#include "umcxray.h"
#include "uxlog.h"

extern struct modlinkage umcxray_modlinkage;

int
_init(void)
{
    int error;
    error = mod_install(&umcxray_modlinkage);
    if (error == 0)
    {
        INFO("UMCXray loaded!");
    }
    return (error);
}

int
_fini(void)
{
    int error;
    error = mod_remove(&umcxray_modlinkage);
    if (error == 0)
    {
        INFO("UMCXray unloaded!");
    }
    return (error);
}

int
_info(struct modinfo *modinfop)
{
    return (mod_info(&umcxray_modlinkage, modinfop));
}
