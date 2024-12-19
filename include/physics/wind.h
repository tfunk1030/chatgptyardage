#pragma once

struct Point3D {
    double x;
    double y;
    double z;
    
    Point3D(double x = 0.0, double y = 0.0, double z = 0.0)
        : x(x), y(y), z(z) {}
};

class Wind {
public:
    Wind(double speed, double direction);
    
    // Apply wind effect to a position, considering ball velocity
    Point3D applyWindEffect(const Point3D& position, double ballVelocity) const;
    
    // Get wind speed
    double getSpeed() const;
    
private:
    double speed;     // in m/s
    double direction; // in degrees (0 = North, 90 = East, etc.)
};
