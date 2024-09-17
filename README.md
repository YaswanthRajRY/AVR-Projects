AVR-Projects

Welcome to the AVR-Projects repository! This repository contains various embedded systems projects based on the AVR family of microcontrollers, such as the ATmega328P. Each project demonstrates different aspects of embedded development, including interfacing with peripherals, using communication protocols, and working with real-time operating systems (RTOS).
Table of Contents

    Projects Overview
    Prerequisites
    Getting Started
    Project List
    Contributing
    License

Projects Overview

This repository showcases my journey into embedded systems programming, with a focus on low-level development for AVR microcontrollers. Projects here cover topics such as:

    Serial Communication (UART, SPI, I2C)
    Peripheral Interfacing (LCD, sensors)
    RTOS Integration and so on.


To run and experiment with these projects, you will need:

    AVR-GCC: AVR toolchain for compiling C code.
    AVRDUDE: For uploading firmware to AVR microcontrollers.
    Programmer: Such as USBasp or Arduino as ISP.
    AVR Microcontroller: Primarily tested with ATmega328P.
    Additional Hardware: Depending on the project (e.g., LCD, sensors, etc.).

Getting Started

Clone the repository:

    [git clone https://github.com/your-username/AVR-Projects.git](https://github.com/YaswanthRajRY/AVR-Projects.git)

Navigate to the project folder of your choice:

    cd AVR-Projects/ProjectName

Compile the code using AVR-GCC:

    make all

Upload the compiled code to your microcontroller using AVRDUDE:

    make flash

Use terminal as a serial monitor (if applicable) to view output or interact with the project.
