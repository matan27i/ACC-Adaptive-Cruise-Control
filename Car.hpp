#pragma once

struct Car {
    double position{0.0};
    double velocity{0.0};

    void update(double dt, double acceleration = 0.0) {
        velocity += acceleration * dt;
        if (velocity < 0.0) {
            velocity = 0.0;
        }
        position += velocity * dt;
    }
};
