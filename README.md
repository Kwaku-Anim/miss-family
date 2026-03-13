# MISS Family: Frugal Infrastructure Intelligence

&gt; Low-cost vision-based structural health monitoring systems for smart buildings using ESP32-CAM

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Platform: ESP32](https://img.shields.io/badge/Platform-ESP32-blue.svg)](https://www.espressif.com/en/products/socs/esp32)

## The Mission

Democratizing structural health monitoring for developing nations through frugal innovation. The MISS (Microstrain Intelligence Sensing Systems) family delivers professional-grade displacement measurement at 97% cost reduction compared to conventional LVDT systems.

## Systems Overview

| System | Status | Breakthrough Feature |
|--------|--------|---------------------|
| **MISS-AFIA** | ✅ Complete | Fully embedded, offline operation |
| **MISS-BUILDING** | ✅ Complete | Wi-Fi networked, smart building ready |
| **MISS-PANYIN** | 🚧 In Progress | Solar-powered, energy autonomous |
| **MISS-CASM** | 🚧 In Progress | Climate-adaptive energy management |
| **MISS-SERWAA** | 🚧 In Progress | High-frequency dynamic capture (50-60Hz) |
| **LoRa Bridge** | 🚧 In Progress | 2km range for remote infrastructure |
| **Optical Mouse** | 🔬 Early Stage | Sub-10μm displacement tracking |

## Technical Highlights

- **10μm displacement resolution** validated against LVDT
- **±0.89 μm zero-drift** over 24-hour testing
- **97% cost reduction** vs. conventional FBG/LVDT systems
- **Constraint-driven optimization** for ESP32-CAM (520KB SRAM)

## Publications

- **MISS-AFIA**: Under review, *Smart Materials and Structures* (Q1)
- **MISS-BUILDING**: Under review, *Buildings* (Q2)

## Quick Start

```bash
# Clone repository
git clone https://github.com/Kwaku-Anim/miss-family.git

# Navigate to system
cd miss-family/miss-afia/firmware

# PlatformIO build
pio run --target upload
