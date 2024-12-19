#include "physics/physics.h"
#include <cmath>

void calculateRelativeVelocity(double velocityX, double velocityY,
                             double windSpeed, double windAngle,
                             double& relativeVelX, double& relativeVelY) {
    // Convert wind angle to radians
    double windAngleRad = windAngle * M_PI / 180.0;
    
    // Calculate wind components
    // For headwind (180°), cos(180°) = -1, so windVx = windSpeed
    // For tailwind (0°), cos(0°) = 1, so windVx = -windSpeed
    double windVx = windSpeed * cos(windAngleRad);
    double windVy = windSpeed * sin(windAngleRad);
    
    // Calculate relative velocity components
    // For headwind, velocityX - windSpeed > velocityX
    // For tailwind, velocityX - (-windSpeed) < velocityX
    relativeVelX = velocityX - windVx;
    relativeVelY = velocityY - windVy;
}

double getAirDensity(const WeatherData* weatherData) {
    if (!weatherData) {
        return 1.225;  // Standard air density at sea level
    }
    
    // Using the ideal gas law and standard atmospheric equations
    const double R = 287.058;  // Specific gas constant for dry air (J/(kg·K))
    double tempK = weatherData->temperature + 273.15;  // Convert °C to K
    double pressure = weatherData->pressure * 100;     // Convert hPa to Pa
    
    // Basic air density calculation (ρ = P/RT)
    double density = pressure / (R * tempK);
    
    // Adjust for humidity (approximate)
    double vaporPressure = (weatherData->humidity / 100.0) * 
                          (6.1078 * exp((17.27 * weatherData->temperature) / 
                                      (weatherData->temperature + 237.3)));
    density *= (1.0 - 0.378 * vaporPressure / pressure);
    
    return density;
}

double getWindAdjustedSpeed(double speed, const WeatherData* weatherData) {
    if (!weatherData) {
        return speed;
    }
    
    // Get the air density ratio compared to standard conditions
    double densityRatio = getAirDensity(weatherData) / 1.225;
    
    // Adjust wind speed based on air density
    // Denser air has more effect, thinner air has less effect
    return speed * sqrt(densityRatio);
}
