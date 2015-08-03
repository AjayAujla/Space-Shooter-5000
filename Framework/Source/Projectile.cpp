#pragma once

#include "Projectile.h"
#include <iostream>
using namespace std;

#include <glm/ext.hpp>

Projectile::Projectile() : SphereModel() {

}

Projectile::Projectile(Model* model, vec3 cameraLookAtVector) : SphereModel() {
	this->mPosition = model->GetPosition();
	float multiplier = 5.0f;
	this->velocity = cameraLookAtVector * multiplier;
	this->timeFired = 0.0f;

	this->fired = false;
	this->collided = false;
}

Projectile::~Projectile() {
	
}

void Projectile::Update(float deltaTime) {
	if(this->fired) {
		this->move(deltaTime);
	}
	if(this->collided) {
		this->~Projectile();
	}
}

void Projectile::Draw(){
	if(this->fired) {
		SphereModel::Draw();
	}
}

void Projectile::move(float deltaTime) {
	this->mPosition += this->velocity * deltaTime;
}