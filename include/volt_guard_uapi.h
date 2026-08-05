#ifndef VOLT_GUARD_UAPI_H
#define VOLT_GUARD_UAPI_H
#include <linux/types.h> <linux/ioctl.h>
#define VOLT_GUARD_MAGIC 0x56
#define VOLT_GUARD_MODE_LOW 0
#define VOLT_GUARD_MODE_MED 1
#define VOLT_GUARD_MODE_HIGH 2
#define VOLT_GUARD_MODE_MAX 3
struct volt_guard_power_mode { __u32 mode; __u32 power_mw; __u32 voltage_mv; __u32 current_ma; __u64 reserved[4]; };
struct volt_guard_sensor { __s32 temp_celsius; __u32 voltage_mv; __u32 current_ma; __u32 power_mw; __u64 reserved[4]; };
#define VOLT_GUARD_IOCTL_SET_MODE _IOW(VOLT_GUARD_MAGIC,1,struct volt_guard_power_mode)
#define VOLT_GUARD_IOCTL_GET_MODE _IOR(VOLT_GUARD_MAGIC,2,struct volt_guard_power_mode)
#define VOLT_GUARD_IOCTL_GET_SENSORS _IOR(VOLT_GUARD_MAGIC,3,struct volt_guard_sensor)
#endif
