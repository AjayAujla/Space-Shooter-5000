#pragma once

#include "Spaceship.h"
#include "TextureLoader.h"

Spaceship::Spaceship() {
}

Spaceship::Spaceship(int maximumCapacity) : CubeModel(), maximumCapacity(maximumCapacity) {
	this->SetScaling(vec3(0.5f, 1.0f, 3.0f));
	this->SetPosition(vec3(5.0f, 10.0f, 5.0f));
	this->projectileContainer = vector<Projectile*>(this->maximumCapacity);
}

Spaceship::~Spaceship() {
	for(vector<Projectile*>::iterator it = this->projectileContainer.begin(); it != this->projectileContainer.end(); ++it) {
		delete (*it);
	}

	this->projectileContainer.clear();
}

void Spaceship::Update(float deltaTime) {
	Model::Update(deltaTime);
	for(vector<Projectile*>::iterator it = this->projectileContainer.begin(); it != this->projectileContainer.end(); ++it) {
		(*it)->Update(deltaTime);
	}
}

void Spaceship::Draw() {
	CubeModel::Draw();
	for(vector<Projectile*>::iterator it = this->projectileContainer.begin(); it != this->projectileContainer.end(); ++it) {
		if(!(*it)->outOfRange && !(*it)->collided) {
			(*it)->Draw();
		}
	}
}

void Spaceship::shoot(vec3 cameraLookAtVector) {
	if(!this->projectileContainer.empty()) {
		this->clearProjectiles();
	}
	if(this->projectileContainer.size() <= this->maximumCapacity) {
		#if defined(PLATFORM_OSX)
			int textureID = TextureLoader::LoadTexture("Textures/projectileTexture.jpg");
		#else
			int textureID = TextureLoader::LoadTexture("../Assets/Textures/projectileTexture.jpg");
		#endif
		this->projectileContainer.push_back(new Projectile(this, cameraLookAtVector, textureID));
		this->projectileContainer.back()->fired = true;
	}
	/*
	if(this->projectileContainer.size() >= this->maximumCapacity) {
		this->projectileContainer.front()->outOfRange = true;
		this->projectileContainer.erase(this->projectileContainer.begin());
 	}
	*/
}

void Spaceship::clearProjectiles() {
	for(vector<Projectile*>::iterator it = this->projectileContainer.begin(); it != this->projectileContainer.end(); ++it) {
		if((*it)->outOfRange || (*it)->collided) {
			this->projectileContainer.erase(remove(this->projectileContainer.begin(), this->projectileContainer.end(), (*it)), this->projectileContainer.end());
		}
	}

	if(this->projectileContainer.size() == this->maximumCapacity) {
		//this->projectileContainer.erase(this->projectileContainer.begin());
	}
}