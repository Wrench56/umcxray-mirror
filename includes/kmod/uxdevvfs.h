#ifndef UMCXRAY_DEVVFS_H
#define UMCXRAY_DEVVFS_H

#include <sys/sunddi.h>

extern int umcxray_open(dev_t *devp, int flag, int otyp, cred_t *cred_p);
extern int umcxray_close(dev_t dev, int flag, int otyp, cred_t *cred_p);
extern int umcxray_attach(dev_info_t *dip, ddi_attach_cmd_t cmd);
extern int umcxray_detach(dev_info_t *dip, ddi_detach_cmd_t cmd);

#endif // UMCXRAY_DEVVFS_H
