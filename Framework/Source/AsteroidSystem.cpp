//
//  AsteroidSystem.cpp
//  COMP371_Framework
//
//  Created by Mark Massoud on 2015-08-02.
//  Copyright (c) 2015 Concordia. All rights reserved.
//

#include "AsteroidSystem.h"
#include "ParticleDescriptor.h"
#include "ParticleEmitter.h"
#include "EventManager.h"
#include "World.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace glm;


AsteroidSystem::AsteroidSystem(ParticleEmitter* emitter, ParticleDescriptor* descriptor)
: mpDescriptor(descriptor), mpEmitter(emitter)
{
    assert(mpDescriptor != nullptr);
    assert(mpEmitter != nullptr);
    
    // Pre-allocate the maximum number of particles at a give time, according to
    // lifetime and emission rate
    int maxAsteroids = 10; // static_cast<int>(mpDescriptor->emissionRate * (mpDescriptor->totalLifetime + mpDescriptor->totalLifetimeDelta)) + 1;
    
    mInactiveAsteroids.resize(maxAsteroids);
    for (std::list<Asteroid*>::iterator it = mInactiveAsteroids.begin(); it != mInactiveAsteroids.end(); ++it)
    {
        *it = new Asteroid();
    }
}

AsteroidSystem::~AsteroidSystem()
{
    for (std::list<Asteroid*>::iterator it = mInactiveAsteroids.begin(); it != mInactiveAsteroids.end(); ++it)
    {
        delete *it;
    }
    
    
    for (std::list<Asteroid*>::iterator it = mAsteroidList.begin(); it != mAsteroidList.end(); ++it)
    {
        World::GetInstance()->RemoveBillboard(&(*it)->billboard);
        delete *it;
    }
    
    mInactiveAsteroids.resize(0);
    mAsteroidList.resize(0);
}

void AsteroidSystem::Update(float dt)
{
    // Emit particle according to the emission rate
    float averageTimeBetweenEmission = 1.0f / mpDescriptor->emissionRate;
    float randomValue = EventManager::GetRandomFloat(0.0f, 1.0f) * averageTimeBetweenEmission;
    while (mInactiveAsteroids.size() > 0 && randomValue < dt)
    {
        randomValue += averageTimeBetweenEmission;
        
        // emit particle
        // transfer a particle from the inactive pool to the active pool
        Asteroid* newAsteroid = mInactiveAsteroids.back();
        mAsteroidList.push_back(newAsteroid);
        mInactiveAsteroids.pop_back();
        
        // Set particle initial parameters
        newAsteroid->billboard.position = mpEmitter->GetAsteroidRandomPosition();
        newAsteroid->billboard.size = mpDescriptor->initialSize + EventManager::GetRandomFloat(-1.0f, 1.0f) * mpDescriptor->initialSizeDelta;
        newAsteroid->billboard.color = mpDescriptor->initialColor;
        newAsteroid->currentTime = 0.0f;
        newAsteroid->lifeTime = mpDescriptor->totalLifetime + mpDescriptor->totalLifetimeDelta * EventManager::GetRandomFloat(-1.0f, 1.0f);
        newAsteroid->velocity = mpDescriptor->velocity;
        
        
        //1
        float randomVelocityRotationDegrees = EventManager::GetRandomFloat(0.0f, 1.0f) * this->mpDescriptor->velocityDeltaAngle;
        vec3 normalToVelocityVector = cross(vec3(0.5, 0.5, 0.5), newAsteroid->velocity);
        mat4 rotationMatrix = rotate(mat4(1.0f), randomVelocityRotationDegrees, normalToVelocityVector);
        newAsteroid->velocity = vec3(rotationMatrix * vec4(newAsteroid->velocity, 0.0f));
        
//        //2
//        float randomRotationAngle = EventManager::GetRandomFloat(0.0f, 1.0f) * 360.0f;
//        mat4 rotationMatrixAroundVelocityVector = rotate(mat4(1.0f), randomRotationAngle, this->mpDescriptor->velocity);
//        newAsteroid->velocity = vec3(rotationMatrixAroundVelocityVector * vec4(newAsteroid->velocity, 1.0f));
        
        World::GetInstance()->AddBillboard(&newAsteroid->billboard);
    }
    
    
    for (std::list<Asteroid*>::iterator it = mAsteroidList.begin(); it != mAsteroidList.end(); )
    {
        Asteroid* p = *it;
        p->currentTime += dt;
        
        //position
        // TODO: modify so that it always goes toward the World origin vec3(0.0f, 0.0f, 0.0f)
        p->billboard.position -= p->velocity * dt + 0.5f * this->mpDescriptor->acceleration * powf(dt, 2.0f);
        
        //velocity
        p->velocity += this->mpDescriptor->acceleration * dt; // v_final = v_initial + a * t
        
        //size
//        p->billboard.size += this->mpDescriptor->sizeGrowthVelocity * dt;
        p->billboard.size = vec2(2.0f, 2.0f);
        
        //color
        p->billboard.color = vec4(0.05f, 1.0f, 0.05f, 1.0f);  // green color
        
        // Particles are destroyed if expired
        // Remove from the send particle to inactive list
        // Remove the billboard from the world
        
        // TODO: modify so that asteroid dies if:
        // 1: asteroid has been shot x times and has no more lives
        // 2: asteroid has reached World origin vec3(0.0f, 0.0f, 0.0f)
        if (p->currentTime > p->lifeTime)
        {
            mInactiveAsteroids.push_back(*it);
            
            World::GetInstance()->RemoveBillboard(&(*it)->billboard);
            it = mAsteroidList.erase(it);
        }
        else
        {
            ++it;
        }
    }
}