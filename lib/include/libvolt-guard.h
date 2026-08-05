#ifndef LIBVOLT_GUARD_H
#define LIBVOLT_GUARD_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
struct volt_guard_handle;
struct volt_guard_handle *volt_guard_open(const char *path);
void volt_guard_close(struct volt_guard_handle *h);
int volt_guard_set_mode(struct volt_guard_handle *h, uint32_t mode, uint32_t power_mw);
int volt_guard_get_mode(struct volt_guard_handle *h, uint32_t *mode, uint32_t *power_mw);
int volt_guard_get_sensors(struct volt_guard_handle *h, int32_t *temp, uint32_t *voltage, uint32_t *current, uint32_t *power);
#ifdef __cplusplus
}
#endif
#endif
