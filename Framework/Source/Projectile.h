#pragma once

#include <vector>

#include <GLM/glm.hpp>
using namespace glm;

#include "SphereModel.h"

class Projectile: public SphereModel {

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

	bool fired;
	bool collided;

	friend class Gun;
};