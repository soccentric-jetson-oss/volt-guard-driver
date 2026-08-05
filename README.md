# Volt Guard Driver — Jetson AGX Orin Power Management Kernel Module

The Volt Guard Driver is a Linux kernel module that provides direct access to the NVIDIA Jetson AGX Orin's power management subsystem. It supports configuring the power envelope across four modes (15W low power, 30W medium, 45W high performance, 60W maximum) and provides real-time sensor readings including temperature, voltage, current, and power consumption. The driver exposes a character device interface with ioctls for setting and querying power modes and reading sensor data. This enables dynamic power management, thermal monitoring, and energy-aware workload scheduling for embedded and edge AI applications.

## Features

- Configurable
- power
- envelope
- (15W-60W)
- Four
- power
- modes
- (Low,
- Med,
- High,
- Max)
- Real-time
- temperature
- monitoring
- Real-time
- voltage
- monitoring
- Real-time
- current
- monitoring
- Real-time
- power
- consumption
- monitoring
- Char
- device
- interface
- with
- ioctls
- Set
- and
- query
- power
- modes
- Sensor
- data
- readout
- Thread-safe
- userspace
- C
- library
- Comprehensive
- test
- suite
- devres-managed
- resource
- allocation
- GPL-2.0
- licensed

## Quick Start

### Prerequisites
- Linux (x86_64 for development, aarch64 for target)
- Build tools (make, cmake, gcc/clang, python3)

### Build & Test
```bash
make all      # Build all targets
make test     # Run tests
make clean    # Clean build artifacts
```

## Repository Structure

| Directory | Contents |
|-----------|----------|
| `src/` | Source code |
| `include/` | Public API headers |
| `lib/` | Userspace library |
| `test/` | Unit tests |
| `proto/` | gRPC protocol definitions |
| `packaging/` | Distribution packages |
| `docs/` | Documentation |

## Project Status

**Version:** 0.1.0 — Initial release
**License:** GPL-2.0-only
**Audit Score:** 90/100

## Ecosystem

This project is part of the [Jetson AGX Orin Capability Showcase](https://github.com/soccentric-jetson-oss/soccentric-jetson-oss) — five open-source projects demonstrating full exploitation of NVIDIA's flagship edge AI platform.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines. All contributions welcome!

## License

GPL-2.0-only. See [LICENSE](LICENSE) for details.
