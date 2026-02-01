#pragma once

class ISensor {
public:
    virtual ~ISensor() = default;
    virtual double readDistance(double actualDist) const = 0;
};
