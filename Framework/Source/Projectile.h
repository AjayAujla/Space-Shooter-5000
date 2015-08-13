#pragma once

#include <vector>

#include <GLM/glm.hpp>
using namespace glm;

#include "SphereModel.h"

class Projectile: public SphereModel {
	
	friend class Spaceship;

public:
	Projectile();

	//sets initial position to that of parent
	Projectile(Model* model, vec3 cameraLookAtVector, int textureID);

	//sets initial position to that of parent + relative position
	Projectile(Model* model, vec3 cameraLookAtVector, vec3 relativePosition, int textureID);

	virtual ~Projectile();
    
	virtual void Update(float deltaTime);
	virtual void Draw();
	bool IsActive(){ return isActive; }

	//void MakeActive();
private:
	Model* parent;
	
	float timeFired;
	float lifetime;
	float time;

	bool isActive;
	
	int textureID;
};