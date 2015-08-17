#include "Asteroid.h"
#include <iostream>
using namespace std;

#include <glm/ext.hpp>
#include <GL/glew.h>

Asteroid::Asteroid(vec3 position, int textureID) : SphereModel(textureID), lifeTime(10.0f), mTime(0.0f), active(false) {
    this->mPosition = position; //+= vec3(model->GetWorldMatrix()[3]);
	//velocity set by callers since Asteroids are re-used
}

Asteroid::~Asteroid() {
}

void Asteroid::Update(float deltaTime) {
	//call model update to move according to velocity. update velocity as necessary first
	mTime += deltaTime;
	Model::Update(deltaTime);

	if (mTime >= lifeTime) active = false;

	//Simon Commented out below to work with Models now
	//move position towards origin
    //vec3 worldOrigin = vec3(0.0f, 0.0f, 0.0f);
    //vec3 currentPosition = this->GetPosition();
    //vec3 difference = currentPosition - worldOrigin;
    
    //this->mPosition -= difference * deltaTime;
//        float p = bSpline(deltaTime);
//    this->SetPosition(vec3(p,p,p));
    
    //    difference = currentPosition - vec3(finalPosition, 1);
    
}

void Asteroid::Draw(){
    SphereModel::Draw();
}

ParticleSystem* Asteroid::getParticleSystem() {
    return this->mParticleSystem;
}

void Asteroid::setParticleSystem(ParticleSystem* ps) {
    this->mParticleSystem = ps;
}

float Asteroid::bSpline(float t) {
    
    float x = 3*pow(t, 2) - 6*pow(t, 3);
    float z = 3*pow(t, 2) - 6*pow(t, 3);
    
    cout << "x: " << x << ",z: " << z << endl;
    
    float y = pow(t, 3) - 6*pow(t, 2) + 11*t + 6;
    
    return y;
}
