
# STM32 Real-Time Robotics Controller

Real-time embedded control firmware developed on the **STM32F446RE** using **FreeRTOS** and an **MPU6050 IMU**.

## Features

* MPU6050 sensor acquisition over I2C
* 100 Hz real-time sensor scheduling
* FreeRTOS tasks and inter-task message queues
* PID-based attitude control loop
* PWM actuator interface
* Fault detection and system state management
* Independent watchdog-based recovery
* UART telemetry/debug output

## Architecture

```text
MPU6050
   │
   │ I2C
   ▼
Sensor Task
   │
   │ IMU Queue
   ▼
Control Task
   │
   │ PID Command
   ▼
PWM / Motor Interface
   │
   ▼
Actuator
```

## Hardware

* STM32F446RE
* MPU6050 IMU

## Software

* C
* STM32 HAL
* FreeRTOS / CMSIS-RTOS2
* STM32CubeIDE / CubeMX

## Current Status

The project is an embedded control **prototype** with a PWM actuator interface. Physical motor/encoder integration and robotics middleware integration are planned as future work.

## Future Work

* Motor and encoder integration
* Closed-loop velocity control
* CAN communication
* Python telemetry and visualization
* ROS 2 integration
