# MCU-1101 (HS1101 + 555 Timer) Humidity Sensor Reader

This Arduino project reads the output frequency from the **MCU-1101 humidity module**, which combines an **HS1101 capacitive humidity sensor** with a **555 timer circuit**. The output frequency changes based on relative humidity and is read via interrupt on a digital pin.

---

## 🧰 Hardware Used

- **MCU-1101 Module** (HS1101 sensor + 555 timer)
- **Arduino Uno (or compatible board)**
- Jumper wires

---

## ⚙️ How It Works

- The **555 timer** in the module outputs a square wave signal whose frequency varies with humidity.
- The **HS1101** sensor changes its capacitance with humidity, which affects the 555 timer's oscillation.
- The Arduino counts rising edges on the signal pin for a set duration.
- It calculates the signal frequency and converts it to an approximate **relative humidity (RH%)**.

---

## 📌 Wiring

| Module Pin | Arduino Pin |
|------------|-------------|
| Signal     | D2          |
| VCC        | 5V          |
| GND        | GND         |

> Uses **interrupt on pin 2 (INT0)** by default.

---

## 📦 Arduino Libraries

No external libraries are required. Uses built-in `Wire.h` and standard interrupt handling.


