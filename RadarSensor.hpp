#pragma once

#include "ISensor.hpp"
#include <random>

class RadarSensor : public ISensor {
public:
    explicit RadarSensor(double noiseStdDev = 0.5);

    double readDistance(double actualDist) const override;

private:
    double noiseStdDev_;
    mutable std::mt19937 rng_;
    mutable std::normal_distribution<double> noiseDist_;
};
