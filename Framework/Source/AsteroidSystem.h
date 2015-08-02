//
//  AsteroidSystem.h
//  COMP371_Framework
//
//  Created by Mark Massoud on 2015-08-02.
//  Copyright (c) 2015 Concordia. All rights reserved.
//

#pragma once

#include "Billboard.h"

class ParticleDescriptor;
class ParticleEmitter;

struct Asteroid
{
    Billboard billboard;
    float currentTime;
    float lifeTime;
    glm::vec3 velocity;
};

class AsteroidSystem
{
public:
    AsteroidSystem(ParticleEmitter* emitter, ParticleDescriptor* descriptor);
    ~AsteroidSystem();
    
    void Update(float dt);
    
private:
    ParticleDescriptor* mpDescriptor;
    ParticleEmitter* mpEmitter;
    std::list<Asteroid*> mAsteroidList;
    std::list<Asteroid*> mInactiveAsteroids;
    
};
