#include "libvolt-guard.h"
#include <fcntl.h> <unistd.h> <stdlib.h> <errno.h> <sys/ioctl.h>
#define VOLT_GUARD_MAGIC 0x56
#define VOLT_GUARD_IOCTL_SET_MODE _IOW(VOLT_GUARD_MAGIC,1,uint32_t[2])
#define VOLT_GUARD_IOCTL_GET_MODE _IOR(VOLT_GUARD_MAGIC,2,uint32_t[2])
#define VOLT_GUARD_IOCTL_GET_SENSORS _IOR(VOLT_GUARD_MAGIC,3,int32_t[4])
struct volt_guard_handle{int fd;};
struct volt_guard_handle*volt_guard_open(const char*p){if(!p){errno=EINVAL;return NULL;}int f=open(p,O_RDWR);if(f<0)return NULL;struct volt_guard_handle*h=calloc(1,sizeof(*h));if(!h){close(f);return NULL;}h->fd=f;return h;}
void volt_guard_close(struct volt_guard_handle*h){if(!h)return;close(h->fd);free(h);}
int volt_guard_set_mode(struct volt_guard_handle*h,uint32_t m,uint32_t p){if(!h)return -EINVAL;uint32_t a[2]={m,p};int r=ioctl(h->fd,VOLT_GUARD_IOCTL_SET_MODE,a);return r<0?-errno:0;}
int volt_guard_get_mode(struct volt_guard_handle*h,uint32_t*m,uint32_t*p){if(!h||!m||!p)return -EINVAL;uint32_t a[2]={0};int r=ioctl(h->fd,VOLT_GUARD_IOCTL_GET_MODE,a);if(r<0)return -errno;*m=a[0];*p=a[1];return 0;}
int volt_guard_get_sensors(struct volt_guard_handle*h,int32_t*t,uint32_t*v,uint32_t*c,uint32_t*p){if(!h||!t||!v||!c||!p)return -EINVAL;int32_t a[4]={0};int r=ioctl(h->fd,VOLT_GUARD_IOCTL_GET_SENSORS,a);if(r<0)return -errno;*t=a[0];*v=(uint32_t)a[1];*c=(uint32_t)a[2];*p=(uint32_t)a[3];return 0;}
