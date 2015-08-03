#pragma once

#include <vector>

#include <GLM/glm.hpp>
using namespace glm;

#include "SphereModel.h"

class Projectile: public SphereModel {
	
	friend class Gun;

public:
	Projectile();
	Projectile(Model* model, vec3 cameraLookAtVector);
	virtual ~Projectile();
    
	virtual void Update(float deltaTime);
	virtual void Draw();

	void move(float deltaTime);

private:
	vec3 velocity;
	
	float timeFired;
	float lifeTime;

	bool fired;
	bool collided;
	bool outOfRange;
};