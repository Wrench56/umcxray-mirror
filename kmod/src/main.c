#include <sys/types.h>
#include <sys/conf.h>
#include <sys/ddi.h>
#include <sys/sunddi.h>
#include <sys/modctl.h>
#include <sys/cmn_err.h>

#include "umcxray.h"

#define MODTAG MODNAME ": "

static struct modlmisc modlmisc = {
    &mod_miscops,
    "IllumOS UMC Xray"
};

static struct modlinkage modlinkage = {
    MODREV_1,
    &modlmisc,
    NULL
};

int
_init(void)
{
    int error;
    error = mod_install(&modlinkage);
    if (error == 0)
    {
        cmn_err(CE_NOTE, MODTAG "UMCXray loaded!");
    }
    return (error);
}

int
_fini(void)
{
    int error;
    error = mod_remove(&modlinkage);
    if (error == 0)
    {
        cmn_err(CE_NOTE, MODTAG "UMCXray unloaded!");
    }
    return (error);
}

int
_info(struct modinfo *modinfop)
{
    return (mod_info(&modlinkage, modinfop));
}
