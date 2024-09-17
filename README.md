# AVR-Projects

Welcome to the AVR-Projects repository! This repository contains various embedded systems projects based on the AVR family of microcontrollers, such as the ATmega328P. Each project demonstrates different aspects of embedded development, including interfacing with peripherals, using communication protocols, and working with real-time operating systems (RTOS).

## Projects Overview

This repository showcases my journey into embedded systems programming, with a focus on low-level development for AVR microcontrollers. Projects here cover topics such as:

1. Serial Communication (UART, SPI, I2C)
2. Peripheral Interfacing (LCD, sensors)
3. RTOS Integration and many

## Prerequisites

To run and experiment with these projects, you will need:

- **AVR-GCC**: AVR toolchain for compiling C code.
- **AVRDUDE**: For uploading firmware to AVR microcontrollers.
- **Programmer**: Such as USBasp or Arduino as ISP.
- **AVR Microcontroller**: Primarily tested with ATmega328P.
- **Additional Hardware**: Depending on the project (e.g., LCD, sensors, etc.).

## Getting Started

1. Clone the repository:
    ```
    gh repo clone YaswanthRajRY/AVR-Projects
    ```

2. Navigate to the project folder of your choice:
    ```
    cd AVR-Projects/ProjectName
    ```

3. Compile the code using AVR-GCC:
    ```
    make all
    ```

4. Upload the compiled code to your microcontroller using AVRDUDE:
    ```
    make flash
    ```

5. Use a terminal as a serial monitor (if applicable) to view output or interact with the project.
