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

/* Boot and power sequencing */
#define VOLT_GUARD_BOOT_NORMAL 0
#define VOLT_GUARD_BOOT_RECOVERY 1
#define VOLT_GUARD_BOOT_DFU     2

/* Watchdog control */
struct volt_guard_watchdog {
    __u32 timeout_sec;
    __u32 action;
    __u32 reserved[4];
};

/* Firmware update */
struct volt_guard_firmware {
    __u32 slot;
    __u32 size;
    __u64 data_addr;
    __u32 crc32;
    __u32 reserved[4];
};

/* DDR tuning */
struct volt_guard_ddr_timing {
    __u32 frequency_hz;
    __u32 voltage_mv;
    __u32 timing_mode;
    __u32 reserved[4];
};

#define VOLT_GUARD_IOCTL_SET_BOOT_MODE  _IOW(VOLT_GUARD_MAGIC, 4, __u32)
#define VOLT_GUARD_IOCTL_SET_WATCHDOG   _IOW(VOLT_GUARD_MAGIC, 5, struct volt_guard_watchdog)
#define VOLT_GUARD_IOCTL_KICK_WATCHDOG  _IO(VOLT_GUARD_MAGIC, 6)
#define VOLT_GUARD_IOCTL_START_FW_UPDATE _IOW(VOLT_GUARD_MAGIC, 7, struct volt_guard_firmware)
#define VOLT_GUARD_IOCTL_SET_DDR_TIMING  _IOW(VOLT_GUARD_MAGIC, 8, struct volt_guard_ddr_timing)
