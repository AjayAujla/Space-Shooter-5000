#pragma once

#include <vector>
using namespace std;

#include "Projectile.h"
#include "CubeModel.h"

class Gun : public CubeModel {

public:
	Gun();
	Gun(int maximumCapacity);
	virtual ~Gun();
	
	virtual void Update(float deltaTime);
	virtual void Draw();

	void shoot(vec3 cameraLookAtVector);
	void clearProjectiles();

	vector<Projectile*> getProjectileContainer();

private:
	vector<Projectile*> projectileContainer;
	vec3 cameraLookAtVector;
	int maximumCapacity;
};