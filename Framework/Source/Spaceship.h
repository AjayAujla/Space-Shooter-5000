#pragma once

#include <vector>
using namespace std;

#include "Projectile.h"
#include "CubeModel.h"

class Spaceship : public CubeModel {

public:
	Spaceship();
	Spaceship(int maximumCapacity);
	virtual ~Spaceship();
	
	virtual void Update(float deltaTime);
	virtual void Draw();

	void shoot(vec3 cameraLookAtVector);
	void clearProjectiles();

	vector<Projectile*> getProjectileContainer() {return this->projectileContainer;}

private:
	vector<Projectile*> projectileContainer;
	vec3 cameraLookAtVector;
	int maximumCapacity;

};