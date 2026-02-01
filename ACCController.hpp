#pragma once

#include "ISensor.hpp"
#include "Car.hpp"
#include <memory>

class ACCController {
public:
    explicit ACCController(std::unique_ptr<ISensor> sensor,
                          double safeDistance = 20.0,
                          double kP = 0.5,
                          double maxAccel = 3.0,
                          double maxDecel = -5.0);

    void update(double dt, Car& egoCar, const Car& targetCar);

    double getLastMeasuredDistance() const { return lastMeasuredDistance_; }
    double getSafeDistance() const { return safeDistance_; }

private:
    std::unique_ptr<ISensor> sensor_;
    double safeDistance_;
    double kP_;
    double maxAccel_;
    double maxDecel_;
    double lastMeasuredDistance_{0.0};

    double clamp(double value, double minVal, double maxVal) const;
};
