# MCU Co-Processor Firmware

## Architecture
The Volt Guard system uses a Cortex-M class MCU for real-time power management:
- I2C/SPI communication between MPU and MCU
- MCU handles: voltage sensing, current monitoring, thermal trips
- MPU handles: policy decisions, user interface, logging

## FreeRTOS Integration
```c
/* MCU firmware task for power monitoring */
void vPowerMonitorTask(void *pvParameters) {
    while (1) {
        read_voltage_sensor();
        read_current_sensor();
        read_temperature_sensor();
        if (over_current_detected()) emergency_shutdown();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
```

## Build
```bash
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Os -ffreestanding -I. -c mcu_firmware.c
arm-none-eabi-ld -T linker.ld -o mcu_firmware.elf mcu_firmware.o
```
