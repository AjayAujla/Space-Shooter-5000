#pragma once

#include "Gun.h"

Gun::Gun() {
	Gun(2);
}

Gun::Gun(int maximumCapacity) : CubeModel() {
	this->SetScaling(vec3(0.5f, 1.0f, 3.0f));
	this->SetPosition(vec3(5.0f, 10.0f, 5.0f));
	this->projectileContainer = vector<Projectile*>(maximumCapacity);
}

Gun::~Gun() {
	for (Projectile* projectile : this->projectileContainer) {
		delete projectile;
	}

	this->projectileContainer.clear();
}

void Gun::Update(float deltaTime) {
	for (Projectile* projectile : this->projectileContainer) {
		cout << "Ajay: inside gun update projectile container for loop" << endl;
		projectile->Update(deltaTime);
	}
}

void Gun::Draw() {
	//CubeModel::Draw();
	for (Projectile* projectile : this->projectileContainer) {
		projectile->Draw();
	}
}

void Gun::shoot(vec3 cameraLookAtVector) {
	cout << "Ajay: SHOOT" << endl;

	if(!this->projectileContainer.empty()) {
		this->clearProjectiles();
	}
	this->projectileContainer.push_back(new Projectile(this, cameraLookAtVector));
	this->projectileContainer.back()->fired = true;

	cout << "Ajay: fired " << this->projectileContainer.back()->fired << endl
		<< "Ajay: capacity" << this->projectileContainer.capacity() << endl
		<< "Ajay: size " << this->projectileContainer.size() << endl;
}

void Gun::clearProjectiles() {
	if(this->projectileContainer.size() == this->projectileContainer.capacity()) {
		cout << "Ajay: fired " << this->projectileContainer.back()->fired << endl
		<< "Ajay: capacity" << this->projectileContainer.capacity() << endl
		<< "Ajay: size " << this->projectileContainer.size() << endl;
		//this->projectileContainer.erase(this->projectileContainer.begin());
	}
	//this->projectileContainer.erase(remove(this->projectileContainer.begin(), this->projectileContainer.end(), 8), this->projectileContainer.end());
}