# EcoLight Maestro: Time & Intensity Adaptive Street Light Automation

A microcontroller-based **Smart Street Light System** developed using the **LPC2129 (ARM7)** microcontroller in **Embedded C**. The system automatically controls street lighting based on ambient light intensity using an LDR while displaying real-time date and time through the RTC. It also features an interrupt-driven menu for editing RTC settings via a keypad. The project was designed and simulated in **Proteus** and developed using **Keil µVision**.

---

## 📌 Features

- 🌙 Automatic street light control based on ambient light intensity (LDR).
- 🕒 Real-Time Clock (RTC) for displaying current date and time.
- ⚡ External Interrupt (EINT1) for instant access to the RTC settings menu.
- ⌨️ RTC editing using a 4×3 keypad.
- 📅 Edit Hour, Minute, Second, Day, Date, Month, and Year.
- 📟 16×2 LCD interface for displaying time, date, and system status.
- 🧩 Modular driver-based Embedded C implementation.
- 🖥️ Designed and tested in Proteus simulation.

---

## 🛠️ Hardware/Simulation Components

- LPC2129 ARM7 Microcontroller
- LDR Sensor
- 16×2 LCD
- 4×3 Matrix Keypad
- External Push Button (EINT1)
- LED (Street Light)

---

## 💻 Software Used

- Keil µVision
- Proteus 8 Professional
- Embedded C

---

## 📂 Project Structure

```
├── ADC Driver
├── LCD Driver
├── RTC Driver
├── Keypad Driver
├── External Interrupt Driver
├── Delay Driver
└── Main Application
```

---

## ⚙️ Working

1. The LPC2148 continuously reads ambient light intensity using the ADC.
2. During night hours, if low light is detected, the street light (LED) turns ON automatically.
3. Otherwise, the street light remains OFF.
4. The LCD continuously displays the current date and time using the RTC.
5. Pressing the external interrupt button opens the RTC settings menu.
6. The keypad is used to edit the Hour, Minute, Second, Day, Date, Month, and Year.

---

## 🚀 Technologies

- Embedded C
- LPC2148 (ARM7)
- ADC
- RTC
- External Interrupts
- Matrix Keypad Interface
- LCD Interfacing
- Proteus Simulation

---

## 📸 Simulation

The complete project was implemented and verified using **Proteus** simulation and programmed using **Keil µVision**.

---
