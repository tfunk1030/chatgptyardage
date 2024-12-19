#include "physics/physics.h"
#include "physics/trajectory.h"
#include <cmath>

TrajectoryResult calculateTrajectory(double initialSpeed, double launchAngle, 
                                   double spinRate, double windSpeed, double windAngle) {
    const double timeStep = 0.001;  // 1ms time step for better accuracy
    const double dragCoefficient = 0.05;  // Base drag coefficient
    const double liftCoefficient = 0.25;  // Base lift coefficient
    const double airDensity = 1.225;  // kg/m^3 at sea level
    const double ballMass = 0.0459;   // kg (golf ball mass)
    const double ballRadius = 0.0213;  // m (golf ball radius)
    const double ballArea = M_PI * ballRadius * ballRadius;
    
    // Convert angles to radians
    double angleRad = launchAngle * M_PI / 180.0;
    
    // Initial velocity components
    double vx = initialSpeed * cos(angleRad);
    double vy = initialSpeed * sin(angleRad);
    
    // Current position
    double x = 0.0;
    double y = 0.0;
    double prevY = 0.0;  // For interpolating ground intersection
    
    TrajectoryResult result;
    result.trajectory.push_back(TrajectoryPoint(x, y));
    result.apex = 0.0;
    
    // Simulation loop
    while (y >= 0.0 || result.trajectory.empty()) {
        prevY = y;
        
        // Calculate relative velocity components
        double relVx, relVy;
        calculateRelativeVelocity(vx, vy, windSpeed, windAngle, relVx, relVy);
        double relV = sqrt(relVx * relVx + relVy * relVy);
        
        if (relV > 0.001) {  // Avoid division by zero
            // Calculate drag force with Reynolds number adjustment
            double reynoldsNumber = (airDensity * relV * 2 * ballRadius) / 1.81e-5;
            double adjustedDragCoef = dragCoefficient;
            if (reynoldsNumber > 1e5) {
                adjustedDragCoef *= 0.5;  // Account for drag crisis
            }
            
            // Adjust drag based on speed and height
            double speedFactor = relV / initialSpeed;
            double heightFactor = exp(-y / 100.0);  // Less drag at higher altitudes
            adjustedDragCoef *= (0.8 + 0.4 * speedFactor) * heightFactor;
            
            // Calculate lift force (Magnus effect)
            double spinFactor = spinRate / 60.0;  // convert rpm to rps
            double magnusFactor = (2.0 * M_PI * ballRadius * spinFactor) / relV;
            double liftForce = 0.5 * airDensity * liftCoefficient * ballArea * relV * relV * magnusFactor;
            
            // Calculate drag force
            double dragForce = 0.5 * airDensity * adjustedDragCoef * ballArea * relV * relV;
            
            // Increase drag and lift in headwind conditions
            double windAngleRad = windAngle * M_PI / 180.0;
            if (windSpeed > 0) {
                double headwindComponent = cos(windAngleRad);  // Positive for headwind (180°)
                if (headwindComponent > 0) {  // Headwind
                    dragForce *= (1.0 + 0.5 * headwindComponent);  // 50% more drag in headwind
                    liftForce *= (1.0 + 0.3 * headwindComponent);  // 30% more lift in headwind
                }
            }
            
            // Apply forces
            double dragAx = -(dragForce * relVx) / (ballMass * relV);
            double dragAy = -(dragForce * relVy) / (ballMass * relV);
            
            // Magnus force acts perpendicular to velocity
            double magnusAx = -(liftForce * relVy) / (ballMass * relV);
            double magnusAy = (liftForce * relVx) / (ballMass * relV);
            
            // Update velocities
            vx += (dragAx + magnusAx) * timeStep;
            vy += (dragAy + magnusAy - GRAVITY) * timeStep;
        } else {
            // If relative velocity is very small, only apply gravity
            vy -= GRAVITY * timeStep;
        }
        
        // Update position
        x += vx * timeStep;
        y += vy * timeStep;
        
        // Record trajectory point
        result.trajectory.push_back(TrajectoryPoint(x, y));
        
        // Update apex
        if (y > result.apex) {
            result.apex = y;
        }
        
        // Prevent infinite loops
        if (result.trajectory.size() > 10000) {
            break;
        }
    }
    
    // Interpolate final point to exactly hit ground
    if (!result.trajectory.empty() && y < 0.0 && prevY > 0.0) {
        double t = -prevY / (y - prevY);
        x = result.trajectory.back().x - t * vx * timeStep;
        result.trajectory.back() = TrajectoryPoint(x, 0.0);
    }
    
    // Set final distance
    result.distance = result.trajectory.back().x;
    
    return result;
}
