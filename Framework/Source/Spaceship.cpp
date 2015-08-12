#pragma once

#include "Spaceship.h"
#include "Utilities.h"

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
		this->projectileContainer.push_back(new Projectile(this, cameraLookAtVector));
		this->projectileContainer.back()->fired = true;
	}

	Utilities::setConsoleOutputColor(1);
	
	cout 
		<< "shoot: capacity " << this->projectileContainer.capacity() << endl
		<< "shoot: size " << this->projectileContainer.size() << endl 
		<< endl;
	
	Utilities::resetConsoleOutputColor();

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
			
			Utilities::setConsoleOutputColor(2);
			
			cout 
				<< "before 1" << endl 
				<< "erase outofrange/collided: capacity " << this->projectileContainer.capacity() << endl
				<< "erase outofrange/collided: size " << this->projectileContainer.size() << endl;
			
			this->projectileContainer.erase(remove(this->projectileContainer.begin(), this->projectileContainer.end(), (*it)), this->projectileContainer.end());

			cout  
				<< "after 1" << endl
				<< "erase outofrange/collided: capacity " << this->projectileContainer.capacity() << endl
				<< "erase outofrange/collided: size " << this->projectileContainer.size() << endl 
				<< endl;
			
			Utilities::resetConsoleOutputColor();
		}
	}

	if(this->projectileContainer.size() == this->maximumCapacity) {
		
		Utilities::setConsoleOutputColor(3);
			
		cout 
			<< "before 2" << endl 
			<< "erase begin: capacity " << this->projectileContainer.capacity() << endl
			<< "erase begin: size " << this->projectileContainer.size() << endl;
			
		//this->projectileContainer.erase(this->projectileContainer.begin());

		cout 
			<< "after 2" << endl
			<< "erase begin: capacity " << this->projectileContainer.capacity() << endl
			<< "erase begin: size " << this->projectileContainer.size() << endl
			<< endl;
			
		Utilities::resetConsoleOutputColor();

	}
}