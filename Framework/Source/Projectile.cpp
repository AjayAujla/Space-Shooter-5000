#include "Projectile.h"
#include "TextureLoader.h"
#include <iostream>
using namespace std;

#include <glm/ext.hpp>

Projectile::Projectile(Model* model, vec3 cameraLookAtVector, int textureID) : SphereModel(textureID), timeFired(0.0f), time(0.0f), lifetime(5.0f), isActive(false) {
	this->parent = model;
	this->mPosition = model->GetPosition();
	this->velocity = cameraLookAtVector * 20.0f; // trajectory
	this->mScaling = vec3(0.5f, 0.5f, 0.5f);
	this->mass = 0.5f;
}

Projectile::Projectile(Model* model, vec3 cameraLookAtVector, vec3 relativePosition, int textureID) : SphereModel(textureID), timeFired(0.0f), time(0.0f), lifetime(5.0f), isActive(false) {
	this->parent = model;
	this->mPosition = model->GetPosition() + relativePosition;
	this->velocity = cameraLookAtVector * 20.0f; // trajectory
	this->mScaling = vec3(0.5f, 0.5f, 0.5f);
	this->mass = 0.5f;
}

Projectile::~Projectile() {
	
}

void Projectile::Update(float dt) {
	if (isActive){
		Model::Update(dt);
		time += dt;
		if (time > lifetime) isActive = false;
	}
}

void Projectile::Draw(){
	if(isActive) SphereModel::Draw();
}

//void Projectile::MakeActive(Model* model, vec3 cameraLookAtVector, vec3 relativePosition, int textureID){}

