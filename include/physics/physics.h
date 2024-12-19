#pragma once

#include <vector>
#include <cmath>
#include "weather/weather_data.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Physical constants
const double GRAVITY = 9.81;  // m/s^2
const double STANDARD_AIR_DENSITY = 1.225;  // kg/m^3 at sea level

// Struct to represent a trajectory point
struct TrajectoryPoint {
    double x; // Horizontal position (m)
    double y; // Vertical position (m)
    
    TrajectoryPoint(double x = 0.0, double y = 0.0)
        : x(x), y(y) {}
};

// Struct to hold trajectory results
struct TrajectoryResult {
    std::vector<TrajectoryPoint> trajectory; // Collection of points in the trajectory
    double distance; // Total distance traveled (m)
    double apex;     // Maximum height reached (m)
    
    TrajectoryResult()
        : distance(0.0), apex(0.0) {}
};

// Main trajectory calculation function
TrajectoryResult calculateTrajectory(double initialSpeed, double launchAngle, 
                                   double spinRate, double windSpeed, double windAngle);

// Wind and air density calculations
double getAirDensity(const WeatherData* weatherData);
double getWindAdjustedSpeed(double speed, const WeatherData* weatherData);
void calculateRelativeVelocity(double velocityX, double velocityY, 
                             double windSpeed, double windAngle,
                             double& relativeVelX, double& relativeVelY);
