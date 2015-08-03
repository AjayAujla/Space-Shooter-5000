#pragma once

#include "Projectile.h"
#include <iostream>
using namespace std;

#include <glm/ext.hpp>

Projectile::Projectile() : SphereModel() {

}

Projectile::Projectile(Model* model, vec3 cameraLookAtVector) : SphereModel(), timeFired(0.0f), lifeTime(0.0f), fired(false), collided(false), outOfRange(false) {
	// @TODO: update model mPosition based on transformations so it can be retrieved via mPosition easily
	this->mPosition = model->GetPosition(); //+= vec3(model->GetWorldMatrix()[3]);
	this->velocity = cameraLookAtVector * 5.0f; // trajectory
	this->mScaling = cameraLookAtVector * 0.5f; // temporary solution to give ellipse shape pointed towrads the direction that it is shooting
}

Projectile::~Projectile() {
	
}

void Projectile::Update(float deltaTime) {
	/*if(this->outOfRange || this->collided) {
		delete this;
	}*/
	if(this->fired) {
		this->move(deltaTime);
	}
}

void Projectile::Draw(){
	if(this->fired) {
		SphereModel::Draw();
	}
}

void Projectile::move(float deltaTime) {
	this->mPosition += this->velocity * deltaTime;

	// optional. without life time, the bullets continue on thier trajectory
	/*
	this->lifeTime += deltaTime;
	if(this->lifeTime >= 5.0f) {
		this->outOfRange = true;
	}
	*/
}