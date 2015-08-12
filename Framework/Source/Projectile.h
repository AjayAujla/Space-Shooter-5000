#pragma once

#include <vector>

#include <GLM/glm.hpp>
using namespace glm;

#include "SphereModel.h"

class Projectile: public SphereModel {
	
	friend class Spaceship;

public:
	Projectile();
	Projectile(Model* model, vec3 cameraLookAtVector, int textureID);
	virtual ~Projectile();
    
	virtual void Update(float deltaTime);
	virtual void Draw();

	void move(float deltaTime);

	bool isCollided();
	void setCollided(bool collided);

private:
	Model* parent;

	vec3 velocity;
	
	float timeFired;
	float lifeTime;

	bool fired;
	bool collided;
	bool outOfRange;
	
	int textureID;
};