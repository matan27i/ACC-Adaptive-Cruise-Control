# C++ Adaptive Cruise Control (ACC) Simulator

## Overview
This project is a time-domain simulation of an automotive **Adaptive Cruise Control (ACC)** system, implemented in **Modern C++ (C++14)**.

The simulation models the interaction between an "Ego Car" (controlled by the ACC) and a "Target Car" (driving with variable velocity). It demonstrates key concepts in autonomous driving software, including sensor abstraction, feedback control loops, and noisy signal processing.

## Key Features
* **Physics-Based Simulation:** Implements discrete time integration for vehicle kinematics.
* **Control Theory:** Uses a Proportional-Derivative (PD-like) control law to maintain safe distance and relative velocity.
* **Sensor Simulation:** Simulates a Radar sensor with Gaussian noise to mimic real-world hardware imperfections.
* **Modern C++ Design:** Utilizes RAII, Smart Pointers (`std::unique_ptr`), and Polymorphism for robust memory management and modularity.

## Technical Highlights
This project was designed to demonstrate proficiency in system-level programming and software architecture:

* **Memory Management:** Strict ownership semantics using `std::unique_ptr` and `std::move` to prevent memory leaks and ensure zero-overhead abstraction.
* **Polymorphism:** Defines an abstract `ISensor` interface, allowing for easy integration of future sensor types (e.g., Lidar, Camera) without modifying the controller logic.
* **STL Usage:** efficient use of `std::vector`, `std::random` (Mersenne Twister engine), and `<algorithm>`.
* **Const Correctness:** rigorous use of `const` to ensure data integrity and interface clarity.

## System Architecture

### 1. `ISensor` (Interface)
An abstract base class defining the contract for distance measurement.
* *Key Method:* `readDistance(double actualDist)`

### 2. `RadarSensor` (Implementation)
A concrete implementation of `ISensor`.
* Simulates measurement noise using a Normal Distribution (`std::normal_distribution`).
* Demonstrates the handling of stochastic inputs in a deterministic control loop.

### 3. `ACCController` (Logic)
The "Brain" of the system.
* **Input:** Owns a sensor instance via `std::unique_ptr`.
* **Process:** Calculates the error (delta between actual and safe distance) and relative velocity.
* **Output:** Computes the required acceleration/deceleration to maintain safety.
* **Safety:** Implements clamping to ensure acceleration stays within comfortable and physical limits.

### 4. `Car` (Physics)
A structure representing the physical state (Position, Velocity) of a vehicle, updated via Euler integration.

## Building and Running

### Prerequisites
* A C++ compiler (supporting C++ - 14) 
