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

	bool isActive(){ return active; }
	void SetActive(bool a){ active = a; }
    
private:
    float lifeTime;
	float mTime;

	bool active;

    ParticleSystem* mParticleSystem;
    
    float bSpline(float t);
    
};