# Cave Radiation Measurement with Arduino + Geiger Counter

This project investigates radiation levels inside a cave using a Geiger counter connected to an Arduino.

## 🕳️ The Cave

Natural caves may contain elevated radiation due to:
- Radon gas accumulation
- Radioactive minerals in the rocks (e.g. uranium, thorium)
- Poor air circulation

## 📟 Setup

- **Arduino** + **Geiger counter module**
- **microSD card module** for data logging
- Power supply (battery or USB)

The core script: **`geiger.ino`**

### What it does:
- Reads pulses from the Geiger tube
- Counts radiation events per time interval
- Saves data to `DATA3.TXT` on SD card

### Build plot:
- The use next notebook: **`histor.ipynb`**

---
