#include <sys/stat.h>

#include "kmod/uxdevvfs.h"
#include "kmod/uxlog.h"

int
umcxray_open(dev_t *devp, int flag, int otyp, cred_t *cred_p)
{
    if (otyp != OTYP_CHR)
    {
        return (EINVAL);
    }

    return 0;
}

int umcxray_close(dev_t dev, int flag, int otyp, cred_t *cred_p)
{
    return 0;
}

int
umcxray_attach(dev_info_t *dip, ddi_attach_cmd_t cmd)
{
    switch (cmd) {
    case DDI_ATTACH:
        if (ddi_create_minor_node(dip, "umcxray", S_IFCHR, 0,
            DDI_PSEUDO, 0) == DDI_FAILURE) {
            WARN("ddi_create_minor_node() failed");
            return DDI_FAILURE;
        }

        ddi_report_dev(dip);
        return DDI_SUCCESS;

    default:
        return DDI_FAILURE;
    }
}

int
umcxray_detach(dev_info_t *dip, ddi_detach_cmd_t cmd)
{
    switch (cmd) {
    case DDI_DETACH:
        ddi_remove_minor_node(dip, NULL);
        return DDI_SUCCESS;

    default:
        return DDI_FAILURE;
    }
}
