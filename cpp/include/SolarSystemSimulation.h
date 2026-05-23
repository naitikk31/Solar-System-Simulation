#ifndef SOLAR_SYSTEM_SIMULATION_H
#define SOLAR_SYSTEM_SIMULATION_H

#define _USE_MATH_DEFINES
#include <string>
#include <vector>
#include <sstream>
#include "CelestialBody.h"

class SolarSystemSimulation {
public:
    SolarSystemSimulation();
    ~SolarSystemSimulation();
    std::string update(double dt);

private:
    std::vector<CelestialObject*> bodies;
    double time;
    static constexpr double G = 4.0 * M_PI * M_PI;
    
    CelestialObject::Vec3 computeAcceleration(int bodyIndex);
};

#endif // SOLAR_SYSTEM_SIMULATION_H
