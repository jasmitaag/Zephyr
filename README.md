# Hybrid Domestic Direct Air Capture (DAC) with Wind Integration

This project is a compact prototype that combines Direct Air Capture (DAC) technology with a small Vertical Axis Wind Turbine (VAWT) to capture CO₂ from ambient air. It uses wind for both mechanical rotation and as an air source for passive CO₂ absorption, minimizing the need for external energy inputs.

## 🌀 Project Overview

- **Type**: Desk-placeable functional prototype
- **Goal**: Demonstrate a low-energy, domestic-scale CO₂ capture system powered by ambient wind
- **Core Components**:
  - 3D-printed VAWT blade with internal chambers
  - Sorbent panel filled with molecular sieves (1.6–2.5 mm)
  - Sliding door mechanism powered by servo motor
  - Thermal regeneration using insulated nichrome wires
  - Central pole for CO₂ gas outlet and wiring transfer
  - Embedded sensors and microcontroller for system monitoring

## 🛠️ Features

- **Hollow Blade Design** with embedded channels for air, wires, and heat insulation
- **Servo Actuator** controls opening and closing of the sorbent chamber
- **Nichrome Wire Heating** system with PWM control for CO₂ desorption
- **Compact Sorbent Panel** with perforated casing and embedded heating
- **Sensor Suite** including temperature, CO₂, and optional airflow sensors

## 🔧 Components Used

| Component        | Size (mm)       |
|------------------|-----------------|
| Sorbent Panel    | 20 x 20 x 3.5    |
| Molecular Sieves | 1.6–2.5          |
| Servo Motor      | 22.6 x 12 x 30   |
| CO₂ Sensor       | 50 x 50 x 50     |
| ESP Controller   | 50 x 20 x 10     |
| Nichrome Wire    | 24 SWG, 2 meters |
| Other Sensors    | Up to 100 x 100 x 100 |

## 📦 Files

- `Blade_Model.f3d` – Fusion 360 file for the blade with internal design
- `Sorbent_Panel.f3d` – Sorbent panel CAD model
- `Actuator_Assembly.f3d` – Actuator + bracket + door mechanism
- `Regeneration_Test.ino` – Arduino sketch for PWM-controlled heating test
- `Wiring_Schematic.png` – Heating circuit layout

## 🚀 Getting Started

1. Print components using heat-resistant 3D filament (e.g., HTPLA, PC, or Nylon).
2. Assemble the actuator and mount to the blade panel.
3. Insert sorbent material and nichrome heating element.
4. Use Arduino + MOSFET + 9V transformer for regeneration testing.
5. Monitor temperature near the wire using an analog or digital sensor.

## 🧪 Testing Plan

- Test nichrome heating wire independently to ensure it reaches 100°C
- Validate CO₂ sensor near sorbent panel to check absorption/desorption cycle
- Perform a full system integration test with wind simulation (fan/blower)

## 📌 Notes

- The blade design is intentionally oversized to accommodate wiring and actuators
- Vacuum sealing is approximated using grooves + servo-slide panel
- All electronics are enclosed safely with appropriate insulation

---

Made with ❤️ by Dousik  
Contributions, forks, and feedback welcome!
