#pragma once

#include "Projectile.h"
#include "TextureLoader.h"
#include <iostream>
using namespace std;

#include <glm/ext.hpp>

Projectile::Projectile(Model* model, vec3 cameraLookAtVector, int textureID) : SphereModel(textureID), timeFired(0.0f), lifeTime(0.0f), fired(false), collided(false), outOfRange(false) {
	this->parent = model;
	this->mPosition = model->GetPosition();
	this->velocity = cameraLookAtVector * 20.0f; // trajectory
	this->mScaling = vec3(0.5f, 0.5f, 0.5f);
}

Projectile::~Projectile() {
	
}

bool Projectile::isCollided() {
	return this->collided;
}

void Projectile::setCollided(bool collided) {
	this->collided = collided;
}

void Projectile::Update(float deltaTime) {
	Model::Update(deltaTime);
	
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