#include "RadarSensor.hpp"
#include <chrono>

RadarSensor::RadarSensor(double noiseStdDev)
    : noiseStdDev_(noiseStdDev)
    , rng_(static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count()))
    , noiseDist_(0.0, noiseStdDev_)
{
}

double RadarSensor::readDistance(double actualDist) const {
    double noise = noiseDist_(rng_);
    double measuredDist = actualDist + noise;
    return measuredDist > 0.0 ? measuredDist : 0.0;
}
