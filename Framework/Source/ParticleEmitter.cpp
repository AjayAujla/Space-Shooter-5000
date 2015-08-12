//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 15/7/15.
//         with help from Jordan Rutty
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#include "ParticleEmitter.h"
#include "Model.h"

using namespace glm;

ParticleEmitter::ParticleEmitter(glm::vec3 position, const Model* parent)
	: mpParent(parent), mPosition(position)
{
}


// This is a point emitter, nothing is random
// As a small extra task, you could create derived classes
// for more interesting emitters such as line emitters or circular emitters
// In these cases, you would sample a random point on these shapes
glm::vec3 ParticleEmitter::GetRandomPosition()
{
	// @TODO 7 - Position from Parented Emitter
	//
	// Return the position where the particle is emitted.
	// If the emitter is parented, the position is relative to its parent

	vec3 position = this->mPosition;
	if(this->mpParent != NULL) {
		position += vec3(this->mpParent->GetWorldMatrix()[3]); //translation component
	}
	return position;
}

glm::vec3 ParticleEmitter::GetAsteroidRandomPosition()
{
    
    float maxRadius = 15;
    
    float randomX = GetRandomFloat(-maxRadius, maxRadius);
    float randomY = GetRandomFloat(-maxRadius, maxRadius);
    float randomZ = GetRandomFloat(-maxRadius, maxRadius);
    
    vec3 position = vec3(randomX, randomY, randomZ);
    
    return position;
}

float ParticleEmitter::GetRandomFloat(float min, float max)
{
    float value = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    return min + value*(max - min);
}