# ESP32 RGB LED Potentiometer Controller

A smooth and responsive color-mixing system powered by the ESP32. This project maps analog potentiometer inputs to RGB LED channels using hardware-accelerated PWM for seamless color transitions.

## Features

*   **Dynamic Color Mixing:** Cycles through the full RGB color spectrum based on the position of the potentiometer.
*   **Linear Interpolation:** Implements a custom `map_value` function for smooth fading effects across the color wheel.
*   **Hardware-Accelerated PWM:** Utilizes the ESP32 LEDC peripheral for stable, flicker-free light control.
*   **Efficient Processing:** Uses FreeRTOS task delays for responsive performance without taxing the CPU.
*   **Real-time Monitoring:** Outputs color values (R, G, B) and ADC readings to the serial monitor for easy debugging.

## Components

*   **Microcontroller:** ESP32 DevKit V1
*   **Input:** 10k Ohm Potentiometer
*   **Output:** Common Cathode/Anode RGB LED
*   **Accessories:** Breadboard, Jumper Wires, and Resistors (for LED)

## Pin Configuration

| Component | GPIO Pin |
| :--- | :--- |
| Potentiometer (Wiper) | GPIO 36 (ADC1_CHANNEL_0) |
| RGB LED (Red) | GPIO 21 |
| RGB LED (Green) | GPIO 22 |
| RGB LED (Blue) | GPIO 23 |

## How to Run

1. Ensure your **ESP-IDF** development environment is correctly set up.
2. Clone this repository:
   ```bash
   git clone https://github.com/hafidzsyifa77-lab/RGB-LED_project