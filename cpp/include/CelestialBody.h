#ifndef CELESTIAL_BODY_H
#define CELESTIAL_BODY_H

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class CelestialObject{
public:
    struct Vec3{
        double x, y, z;
        Vec3(double x = 0, double y = 0, double z = 0) {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        
        Vec3 operator+(const Vec3& other) const{
            return Vec3(x + other.x, y + other.y, z + other.z); // x + y
        }
        
        Vec3 operator-(const Vec3& other) const{
            return Vec3(x - other.x, y - other.y, z - other.z);
        }
        
        Vec3 operator*(double scalar) const{
            return Vec3(x * scalar, y * scalar, z * scalar);
        }
        
        double magnitude() const{
            return sqrt(x*x + y*y + z*z);
        }
        
        Vec3 normalized() const{
            double mag = magnitude();
            if (mag > 0) return Vec3(x/mag, y/mag, z/mag);
            return Vec3(0, 0, 0);
        }
    };
    
    Vec3 position;
    Vec3 velocity;
    Vec3 acceleration;
    
    virtual void update(double dt) = 0;
    virtual std::string getType() const = 0;
    virtual double getMass() const = 0;
    virtual ~CelestialObject() = default;
};

class CelestialBody : public CelestialObject{
protected:
    std::string name;
    double mass;
    double radius;
    double semiMajorAxis;
    double eccentricity;
    double period;
    double inclination;

public:

    CelestialBody(std::string n, double m, double r, double a, double e, double p, double iDeg){
        name = n;
        mass = m;
        radius = r;
        semiMajorAxis = a;
        eccentricity = e;
        period = p;
        inclination = iDeg * M_PI / 180.0;

        if (semiMajorAxis > 0.0)
            computeInitialState();
        else {
            position = Vec3(0, 0, 0);
            velocity = Vec3(0, 0, 0);
            acceleration = Vec3(0, 0, 0);
        }
    }


    virtual ~CelestialBody() = default;

    void update(double dt) override {
        position = position + velocity * dt + acceleration * (0.5 * dt * dt);
    }
    
    std::string getType() const override {
        return "Body";
    }
    
    double getMass() const override {
        return mass;
    }
    
    void updateVelocity(double dt, const Vec3& newAcceleration){
        velocity = velocity + (acceleration + newAcceleration) * (0.5 * dt);
        acceleration = newAcceleration;
    }

    const std::string& getName() const{ return name; }
    
    friend double calculateSurfaceGravity(const CelestialBody& body){
        // g = G * M / R²
        double radiusMeters = body.radius * 1000.0; // radius km to m
        const double G = 6.674e-11; // m³/(kgs²)
        return (G * body.mass) / (radiusMeters * radiusMeters);
    }
    
    double getSurfaceGravity() const{
        return calculateSurfaceGravity(*this);
    }

protected:
    void computeInitialState(){
        double r = semiMajorAxis * (1 - eccentricity);
        
        position.x = r * cos(0);
        position.y = r * sin(0) * cos(inclination);
        position.z = r * sin(0) * sin(inclination);
        
        const double G_M_sun = 4.0 * M_PI * M_PI; // Gaussian gravitational constant
        
        double v = sqrt(G_M_sun * (2.0/r - 1.0/semiMajorAxis)); // vis-viva eqn
        
        velocity.x = 0;
        velocity.y = v * cos(inclination);
        velocity.z = v * sin(inclination);
        
        acceleration = Vec3(0, 0, 0);
    }
};

class Planet : public CelestialBody{
    std::string planetType;
public:
    Planet(std::string name, double mass, double radius, double semiMajorAxis, double eccentricity, double period, double inclinationDeg, std::string type) : CelestialBody(name, mass, radius, semiMajorAxis, eccentricity, period, inclinationDeg){
        planetType = type;
    }
    
    std::string getType() const override {
        return planetType + " Planet";
    }
    
    std::string getPlanetType() const{ return planetType; }
};

class Star : public CelestialBody{
public:
    Star(std::string name, double mass, double radius) 
        : CelestialBody(name, mass, radius, 0.0, 0.0, 0.0, 0.0){}
    
    std::string getType() const override {
        return "Star";
    }
    
    void update(double dt) override {}
};

#endif // CELESTIAL_BODY_H
