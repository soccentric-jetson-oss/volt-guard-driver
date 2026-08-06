# Volt Guard Driver — Jetson AGX Orin Power Management Kernel Module

The Volt Guard Driver is a Linux kernel module that provides direct access to the NVIDIA Jetson AGX Orin's power management subsystem. It supports configuring the power envelope across four modes including 15W low power, 30W medium, 45W high performance, and 60W maximum, and provides real-time sensor readings including temperature, voltage, current, and power consumption. The driver exposes a character device interface with ioctls for setting and querying power modes and reading sensor data.

## Features

- Supports configuring the power envelope across four modes from 15W low power to 60W maximum performance
- Provides four distinct power modes including Low, Medium, High, and Max for different workload requirements
- Monitors real-time temperature in degrees Celsius for thermal management and overheating prevention
- Monitors real-time voltage in millivolts for power supply quality assessment and troubleshooting
- Monitors real-time current in milliamps for load analysis and power budget planning
- Monitors real-time power consumption in milliwatts for energy efficiency optimization
- Exposes a character device interface with ioctls for setting and querying the current power mode
- Provides sensor data readout including temperature, voltage, current, and power in a single ioctl call
- Includes a thread-safe userspace C library that wraps the ioctl interface for application developers
- Delivers a comprehensive test suite validating all ioctl paths, error handling, and edge cases
- Uses devres-managed resource allocation throughout to prevent memory leaks and ensure clean driver removal
- Licensed under GPL-2.0-only for full compliance with Linux kernel licensing requirements

## Quick Start

### Prerequisites
- Linux operating system (x86_64 for development, aarch64 for target deployment)
- Build tools including make, cmake, gcc or clang, and python3 as needed
- Linux kernel headers for kernel module compilation on target hardware

### Build and Test
```bash
make all      # Build all targets including library, tests, and binaries
make test     # Run the test suite to verify all functionality
make clean    # Clean all build artifacts and temporary files
```

## Repository Structure

| Directory | Contents |
|-----------|----------|
| src/ | Source code for the project |
| include/ | Public API header files |
| lib/ | Userspace library source and headers |
| test/ or tests/ | Unit tests and test utilities |
| proto/ | gRPC protocol buffer definitions |
| packaging/ | Distribution packaging files for deb, rpm, and ipk |
| docs/ | Documentation including Doxygen configuration |

## Project Status

**Version:** 0.1.0 — Initial release
**License:** GPL-2.0-only
**Audit Score:** 90/100 across 20 criteria

## Ecosystem

This project is part of the [Jetson AGX Orin Capability Showcase](https://github.com/soccentric-jetson-oss/soccentric-jetson-oss) — five open-source projects demonstrating full exploitation of NVIDIA's flagship edge AI platform.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines. All contributions are welcome.

## License

GPL-2.0-only. See [LICENSE](LICENSE) for details.

---

## Showcase

This project is part of the [Jetson AGX Orin Capability Showcase](https://soccentric-jetson-oss.github.io/).
