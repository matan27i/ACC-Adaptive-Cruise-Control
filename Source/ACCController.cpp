#include "ACCController.hpp"
#include <cmath>

ACCController::ACCController(std::unique_ptr<ISensor> sensor,
                             double safeDistance,
                             double kP,
                             double maxAccel,
                             double maxDecel)
    : sensor_(std::move(sensor))
    , safeDistance_(safeDistance)
    , kP_(kP)
    , maxAccel_(maxAccel)
    , maxDecel_(maxDecel)
{
}

void ACCController::update(double dt, Car& egoCar, const Car& targetCar) {
    double actualDistance = targetCar.position - egoCar.position;
    lastMeasuredDistance_ = sensor_->readDistance(actualDistance);

    // P-controller: error = measured distance - safe distance
    // Positive error means we're too far -> accelerate
    // Negative error means we're too close -> decelerate
    double error = lastMeasuredDistance_ - safeDistance_;

    // Also factor in relative velocity for smoother control
    double relativeVelocity = targetCar.velocity - egoCar.velocity;

    // Combined control signal
    double acceleration = kP_ * error + 0.3 * relativeVelocity;

    // Clamp acceleration within safe limits
    acceleration = clamp(acceleration, maxDecel_, maxAccel_);

    egoCar.update(dt, acceleration);
}

double ACCController::clamp(double value, double minVal, double maxVal) const {
    if (value < minVal) return minVal;
    if (value > maxVal) return maxVal;
    return value;
}
