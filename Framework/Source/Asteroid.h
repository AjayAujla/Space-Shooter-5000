#pragma once

#include <vector>

#include <GLM/glm.hpp>
using namespace glm;

#include "SphereModel.h"
#include "ParticleSystem.h"

class Asteroid : public SphereModel {
    
public:
    Asteroid();
    Asteroid(vec3 position);
    ~Asteroid();
    
    virtual void Update(float deltaTime);
    virtual void Draw();
    
    ParticleSystem* getParticleSystem();
    void setVelocity(vec3 velocity);
    void setParticleSystem(ParticleSystem* ps);
    
private:
    vec3 mVelocity;
    float lifeTime;
    
    ParticleSystem* mParticleSystem;
    
    vec2 bSpline(float t);
    
};