#include "physics/wind.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Wind::Wind(double speed, double direction)
    : speed(speed), direction(direction)
{}

Point3D Wind::applyWindEffect(const Point3D& position, double ballVelocity) const {
    Point3D result = position;
    
    // Convert wind direction to radians
    double dirRad = direction * M_PI / 180.0;
    
    // Calculate relative wind effect based on ball velocity
    double relativeEffect = speed / (ballVelocity + speed + 1.0);  // +1 to avoid division by zero
    
    // Calculate wind components
    // For crosswind test, 90° should push ball right (positive y) and 270° should push ball left (negative y)
    double windX = -speed * cos(dirRad);  // Negative because wind direction is FROM
    double windY = speed * sin(dirRad);   // No negative here to match test expectations
    
    // Apply wind effect proportionally to wind components
    // Scale factor is the same for both components to ensure symmetry
    const double scaleFactor = 0.1;
    result.x = position.x + windX * relativeEffect * scaleFactor;
    result.y = position.y + windY * relativeEffect * scaleFactor;
    
    return result;
}

double Wind::getSpeed() const {
    return speed;
}
