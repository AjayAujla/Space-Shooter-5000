//
//  AsteroidSystem.h
//  COMP371_Framework
//
//  Created by Mark Massoud on 2015-08-02.
//  Copyright (c) 2015 Concordia. All rights reserved.
//

#pragma once

#include "Asteroid.h"

class ParticleDescriptor;
class ParticleEmitter;
class Asteroid;

class AsteroidSystem
{
public:
    AsteroidSystem(ParticleEmitter* emitter, ParticleDescriptor* descriptor);
    ~AsteroidSystem();
    
    void Update(float dt);
    void Draw();
    
private:
    ParticleDescriptor* mpDescriptor;
    ParticleEmitter* mpEmitter;
    std::vector<Asteroid*> mAsteroidList;
    std::vector<Asteroid*> mInactiveAsteroids;
};
