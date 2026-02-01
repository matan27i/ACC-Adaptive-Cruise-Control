#include "Car.hpp"
#include "RadarSensor.hpp"
#include "ACCController.hpp"

#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <cmath>

int main() {
    // Initialize cars
    Car targetCar{50.0, 15.0};  // Starts 50m ahead, 15 m/s
    Car egoCar{0.0, 20.0};      // Starts at origin, 20 m/s (faster initially)

    // Create ACC controller with radar sensor
    auto radarSensor = std::make_unique<RadarSensor>(0.3);  // 0.3m noise std dev
    ACCController acc(std::move(radarSensor),
                      15.0,   // safe distance (meters)
                      0.4,    // P-gain
                      2.5,    // max acceleration (m/s^2)
                      -4.0);  // max deceleration (m/s^2)

    // Simulation parameters
    constexpr double dt = 0.1;           // 100ms time step
    constexpr int numSteps = 100;

    // Store results for output
    struct SimData {
        double time;
        double targetPos;
        double egoPos;
        double distance;
        double velocity;
    };
    std::vector<SimData> results;
    results.reserve(numSteps + 1);

    // Print CSV header
    std::cout << "time,target_pos,ego_pos,distance,velocity\n";

    // Simulation loop
    for (int step = 0; step <= numSteps; ++step) {
        double time = step * dt;

        // Calculate actual distance
        double actualDistance = targetCar.position - egoCar.position;

        // Store and output current state
        SimData data{time, targetCar.position, egoCar.position,
                     actualDistance, egoCar.velocity};
        results.push_back(data);

        std::cout << std::fixed << std::setprecision(2)
                  << data.time << ","
                  << data.targetPos << ","
                  << data.egoPos << ","
                  << data.distance << ","
                  << data.velocity << "\n";

        // Skip update on last step
        if (step == numSteps) break;

        // Target car drives at variable speed (sinusoidal variation)
        double targetAccel = 1.5 * std::sin(0.3 * time);
        targetCar.update(dt, targetAccel);

        // Update ego car using ACC
        acc.update(dt, egoCar, targetCar);
    }

    return 0;
}
