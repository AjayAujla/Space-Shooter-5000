#pragma once

#include <vector>

#include <GLM/glm.hpp>
using namespace glm;

#include "SphereModel.h"
#include "ParticleSystem.h"

class Asteroid : public SphereModel {
    
public:
    Asteroid();
    Asteroid(vec3 position, int textureID);
    virtual ~Asteroid();
    
    virtual void Update(float deltaTime);
    virtual void Draw();
    
    ParticleSystem* getParticleSystem();
    void setParticleSystem(ParticleSystem* ps);
    
private:
    float lifeTime;
    
    ParticleSystem* mParticleSystem;
    
    float bSpline(float t);
    
};