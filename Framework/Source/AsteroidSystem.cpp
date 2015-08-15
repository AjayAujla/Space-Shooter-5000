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
    
	#if defined(PLATFORM_OSX)
		int textureID = TextureLoader::LoadTexture("Textures/asteroidTexture.jpg");
	#else
		int textureID = TextureLoader::LoadTexture("../Assets/Textures/asteroidTexture.jpg");
	#endif

    // Update Event Manager - Frame time / input / events processing
    
    // Pre-allocate the maximum number of particles at a give time, according to
    // lifetime and emission rate
    int maxAsteroids = static_cast<int>(mpDescriptor->emissionRate * (mpDescriptor->totalLifetime + mpDescriptor->totalLifetimeDelta)) + 1;
    
    mInactiveAsteroids.resize(maxAsteroids);
    for (std::vector<Asteroid*>::iterator it = mInactiveAsteroids.begin(); it != mInactiveAsteroids.end(); ++it)
    {
		*it = new Asteroid(mpEmitter->GetAsteroidRandomPosition(), textureID);
    }
    
}

AsteroidSystem::~AsteroidSystem()
{
    // TODO: DESTROY MODEL STUFF INSTEAD
    for (std::vector<Asteroid*>::iterator it = mInactiveAsteroids.begin(); it != mInactiveAsteroids.end(); ++it)
    {
        delete *it;
    }
    
    
    for (std::vector<Asteroid*>::iterator it = mAsteroidList.begin(); it != mAsteroidList.end(); ++it)
    {
        delete *it;
    }
    
    mInactiveAsteroids.resize(0);
    mAsteroidList.resize(0);
}

void AsteroidSystem::Update(float dt)
{
    // Emit particle according to the emission rate
    float averageTimeBetweenEmission = 30.0f / mpDescriptor->emissionRate;
    float randomValue = EventManager::GetRandomFloat(0.0f, 1.0f) * averageTimeBetweenEmission;
    
    while (mInactiveAsteroids.size() > 0 && randomValue < dt)
    {
        randomValue += averageTimeBetweenEmission;
        
        Asteroid* newAsteroid = mInactiveAsteroids.back();
        mAsteroidList.push_back(newAsteroid);
        mInactiveAsteroids.pop_back();
        
        newAsteroid->SetPosition(mpEmitter->GetAsteroidRandomPosition());
        
        // giving random size to asteroids
		float randomSize = mpEmitter->GetRandomFloat(0.5, 1.5);
		newAsteroid->SetScaling(vec3(randomSize));

        mpEmitter = new ParticleEmitter(vec3(0.0f, 0.0f, 0.0f), newAsteroid);
        mpDescriptor = new ParticleDescriptor();
        
		mpDescriptor->setInitialSize(vec2(randomSize));

        mpDescriptor->SetAsteroidDescriptor();
        
        
        ParticleSystem* ps = new ParticleSystem(mpEmitter, mpDescriptor);
        
        newAsteroid->setParticleSystem(ps);
    }
    
    for (std::vector<Asteroid*>::iterator it = mAsteroidList.begin(); it != mAsteroidList.end(); )
    {
        Asteroid* a = (*it);
        a->Update(dt);
        a->getParticleSystem()->Update(dt);
        
        // TODO: modify so that asteroid dies if:
        // 1: asteroid has been shot x times and has no more lives
        // 2: asteroid has reached World origin vec3(0.0f, 0.0f, 0.0f)
        if (abs(a->GetPosition().x - a->getTarget().x) <= 2.0f || a->getLifeTime() <= dt)
        {
            mInactiveAsteroids.push_back(a);
            delete a->getParticleSystem();
            it = mAsteroidList.erase(it);
        }
        else
        {
            ++it;
        }
        
    }
    
}

void AsteroidSystem::Draw() {
    
    for(Asteroid* asteroid : mAsteroidList) {
        asteroid->Draw();
    }
    
}