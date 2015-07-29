//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 15/7/15.
//         with help from Jordan Rutty
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#include "ParticleSystem.h"
#include "ParticleDescriptor.h"
#include "ParticleEmitter.h"
#include "EventManager.h"
#include "World.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace glm;
using namespace std;


ParticleSystem::ParticleSystem(ParticleEmitter* emitter, ParticleDescriptor* descriptor)
: mpDescriptor(descriptor), mpEmitter(emitter)
{
    assert(mpDescriptor != nullptr);
    assert(mpEmitter != nullptr);
    
    // Pre-allocate the maximum number of particles at a give time, according to
    // lifetime and emission rate
    int maxParticles = static_cast<int>(mpDescriptor->emissionRate * (mpDescriptor->totalLifetime + mpDescriptor->totalLifetimeDelta)) + 1;
    
    mInactiveParticles.resize(maxParticles);
    for (std::list<Particle*>::iterator it = mInactiveParticles.begin(); it != mInactiveParticles.end(); ++it)
    {
        *it = new Particle();
    }
}

ParticleSystem::~ParticleSystem()
{
	for (std::list<Particle*>::iterator it = mInactiveParticles.begin(); it != mInactiveParticles.end(); ++it)
	{
		delete *it;
	}


	for (std::list<Particle*>::iterator it = mParticleList.begin(); it != mParticleList.end(); ++it)
	{
		World::GetInstance()->RemoveBillboard(&(*it)->billboard);
		delete *it;
	}

	mInactiveParticles.resize(0);
	mParticleList.resize(0);
}

void ParticleSystem::Update(float dt)
{
    // Emit particle according to the emission rate
    float averageTimeBetweenEmission = 1.0f / mpDescriptor->emissionRate;
    float randomValue = EventManager::GetRandomFloat(0.0f, 1.0f) * averageTimeBetweenEmission;
    while (mInactiveParticles.size() > 0 && randomValue < dt)
    {
        randomValue += averageTimeBetweenEmission;
        
        // emit particle
        // transfer a particle from the inactive pool to the active pool
        Particle* newParticle = mInactiveParticles.back();
        mParticleList.push_back(newParticle);
        mInactiveParticles.pop_back();
        
        // Set particle initial parameters
        newParticle->billboard.position = mpEmitter->GetRandomPosition();
        newParticle->billboard.size = mpDescriptor->initialSize + EventManager::GetRandomFloat(-1.0f, 1.0f) * mpDescriptor->initialSizeDelta;
        newParticle->billboard.color = mpDescriptor->initialColor;
        newParticle->currentTime = 0.0f;
        newParticle->lifeTime = mpDescriptor->totalLifetime + mpDescriptor->totalLifetimeDelta * EventManager::GetRandomFloat(-1.0f, 1.0f);
        newParticle->velocity = mpDescriptor->velocity;
        
        // @TODO 6 - Initial Random Particle Velocity vector
        //
        // Adjust the random velocity according to a random vertical angle variation on a cone
        //
        // Step 1 : You can rotate the velocity vector by a random number between 0 and
        //          mpDescriptor->velocityDeltaAngle.
        // Step 2 : You can rotate the result in step 1 by an random angle from 0 to
        //          360 degrees about the original velocity vector

		//get any vector which is not the velocity vector to take a cross product with (so that we can have a rotation axis perp. to the velocity vector)
		vec3 any(0.0f,0.0f,1.0f);
		if (any == mpDescriptor->velocity)
			any = vec3(1.0f, 0.0f, 0.0f);
		vec3 temp = vec3(glm::rotate(mat4(1.0f),EventManager::GetRandomFloat(0.0f, mpDescriptor->velocityDeltaAngle), cross(mpDescriptor->velocity,any)) * vec4(newParticle->velocity,1.0f));
		//now rotate about the original velocity vector to randomize over the whole circle around.
		temp = vec3(glm::rotate(mat4(1.0f), EventManager::GetRandomFloat(0.0f,360.0f), mpDescriptor->velocity) * vec4(temp, 1.0f));
		newParticle->velocity = temp;

        World::GetInstance()->AddBillboard(&newParticle->billboard);
    }
    
    
    for (std::list<Particle*>::iterator it = mParticleList.begin(); it != mParticleList.end(); )
    {
        Particle* p = *it;
		p->currentTime += dt;

        // @TODO 5 - Update each particle's parameter
        //
        // Update the velocity and position of the particle from the acceleration of the descriptor
        // Update the size of the particle according to its growth
        // Update The color is also updated in 3 phases
        //
        //
        // Phase 1 - Initial: from t = [0, fadeInTime] - Linearly interpolate between initial color and mid color
        // Phase 2 - Mid:     from t = [fadeInTime, lifeTime - fadeOutTime] - color is mid color
        // Phase 3 - End:     from t = [lifeTime - fadeOutTime, lifeTime]
                
        
        // ...

		//use kinematics formulas to update first the position and then the velocity (must be updated for the formulas to be exact in the next time step)
        p->billboard.position += p->velocity * dt + 0.5f*mpDescriptor->acceleration*dt*dt;
		p->velocity += mpDescriptor->acceleration * dt;
		//condition color on time, and linearly interpolate where necessary
		if (p->currentTime < mpDescriptor->fadeInTime){
			p->billboard.color = mpDescriptor->initialColor + p->currentTime / mpDescriptor->fadeInTime * (mpDescriptor->midColor - mpDescriptor->initialColor);
		}
		else if (p->currentTime < p->lifeTime - mpDescriptor->fadeOutTime){
			p->billboard.color = mpDescriptor->midColor;
		}
		else{
			p->billboard.color = mpDescriptor->midColor + (mpDescriptor->endColor - mpDescriptor->midColor)*(p->currentTime - p->lifeTime + mpDescriptor->fadeOutTime) / (mpDescriptor->fadeOutTime);
		}
		//add the delta size for this time step
        p->billboard.size += mpDescriptor->sizeGrowthVelocity * dt;
        // ...
        
        
        
        // Particles are destroyed if expired
        // Remove from the send particle to inactive list
        // Remove the billboard from the world
        if (p->currentTime > p->lifeTime)
        {
            mInactiveParticles.push_back(*it);
            
            World::GetInstance()->RemoveBillboard(&(*it)->billboard);
            it = mParticleList.erase(it);
        }
        else
        {
            ++it;
        }
    }
    
    

}
