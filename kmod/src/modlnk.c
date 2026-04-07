#include <sys/conf.h>
#include <sys/types.h>
#include <sys/ddi.h>
#include <sys/sunddi.h>

#include "umcxray.h"

static struct cb_ops cb_ops = {
    nodev,
    nodev,
    nodev,
    nodev,
    nodev,
    nodev,
    nodev,
    nodev,
    nodev,
    nodev,
    nodev,
    nochpoll,
    nodev,
    NULL,
    D_MP | D_64BIT,
    CB_REV,
    nodev,
    nodev
};

static struct dev_ops dev_ops = {
    DEVO_REV,
    0,
    nulldev,
    nulldev,
    nulldev,
    nulldev,
    nulldev,
    nodev,
    &cb_ops,
    NULL,
    NULL,
    ddi_quiesce_not_needed
};

static struct modldrv modldrv = {
    &mod_miscops,
    "IllumOS UMC Xray " UMCXRAY_VERSION,
    &dev_ops
};

struct modlinkage umcxray_modlinkage = {
    MODREV_1,
    &modldrv,
    NULL
};
