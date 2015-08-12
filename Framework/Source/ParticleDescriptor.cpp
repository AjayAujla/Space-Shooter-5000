//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 15/7/15.
//         with help from Jordan Rutty
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//
#include "ParticleDescriptor.h"


using namespace glm;

ParticleDescriptor::ParticleDescriptor()
{
    SetFountainDescriptor();
}

void ParticleDescriptor::SetFountainDescriptor()
{
	velocity = vec3(0.0f, 17.0f, 0.0f);
	velocityDeltaAngle = 15;

	acceleration = vec3(0.0f, -7.0f, 0.0f);

	initialSize = vec2(1.2f, 1.2f);
	initialSizeDelta = vec2(0.4f, 0.4f);
	sizeGrowthVelocity = vec2(1.0f, 1.0f);

	initialColor = vec4(0.1f, 0.2f, 0.8f, 0.9f);
	midColor = vec4(2.2f, 1.2f, 0.2f, 2.2f);
	endColor = vec4(1.2f, 0.3f, 0.5f, 0.2f);

	emissionRate = 5.0f;
	fadeInTime = 0.2f;
	fadeOutTime = 4.5f;
	totalLifetime = 2.0f;
	totalLifetimeDelta = 0.3f;
}

void ParticleDescriptor::SetFireDescriptor()
{
	velocity = vec3(0.0f, 2.4f, 0.0f);
	velocityDeltaAngle = 10.0f;

	acceleration = vec3(0, 0, 0);

	initialSize = vec2(5.0f, 5.0f);
	initialSizeDelta = vec2(0.02f, 0.02f);

	sizeGrowthVelocity = vec2(-2.4f, -2.4f);

	initialColor = vec4(0.2f, 0.2f, 1.0f, 1.2f);
	midColor = vec4(1.2f, 1.0f, 0.5f, 0.1f);
	endColor = vec4(0.2f, 0.5f, 0.1f, 0.0f);

	emissionRate = 25.0f;
	fadeInTime = 1.5f;
	fadeOutTime = 0.2f;
	totalLifetime = 1.7f;
	totalLifetimeDelta = 0.0f;
}

void ParticleDescriptor::SetAsteroidDescriptor()
{
    velocity = vec3(0.0f, 1.0f, 0.0f);
    velocityDeltaAngle = 10.0f;
    
    acceleration = vec3(0,0,0);
    
    initialSize = vec2(2.0f, 2.0f);
    initialSizeDelta = vec2(0.02f, 0.02f);
    
    sizeGrowthVelocity = vec2(-2.4f, -2.4f);
    
    initialColor = vec4(0.0f, 0.0f, 1.0f, 0.2f);
    midColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);
    endColor = vec4(1.0f, 1.0f, 1.0f, 0.5f);
    
    emissionRate = 25.0f;
    fadeInTime = 1.5f;
    fadeOutTime = 0.2f;
    totalLifetime = 5.0f;
    totalLifetimeDelta = 0.0f;
}

void ParticleDescriptor::setInitialSize(vec2 size) {
	this->initialSize = size;
}