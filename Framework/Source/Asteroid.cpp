#include "Asteroid.h"
#include "EventManager.h"
#include <iostream>
using namespace std;

#include <glm/ext.hpp>
#include <GL/glew.h>

Asteroid::Asteroid(vec3 position, int textureID) : SphereModel(textureID), lifeTime(0.0f) {
    // @TODO: update model mPosition based on transformations so it can be retrieved via mPosition easily
    this->mPosition = position;
    this->velocity = vec3(2.0f, 2.0f, 2.0f);
    this->lifeTime = 50;
    
    float randomTargetX = EventManager::GetRandomFloat(-30.0f, 30.0f);
    float randomTargetY = EventManager::GetRandomFloat(-30.0f, 30.0f);
    float randomTargetZ = EventManager::GetRandomFloat(-30.0f, 30.0f);
    this->target = vec3(randomTargetX, randomTargetY, randomTargetZ);
}

Asteroid::~Asteroid() {
}

void Asteroid::Update(float deltaTime) {
    
    vec3 currentPosition = this->GetPosition();
    vec3 difference = currentPosition - this->target;
    
    this->mPosition -= difference * deltaTime;
    
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

float Asteroid::getLifeTime() {
    return this->lifeTime;
}

vec3 Asteroid::getTarget() {
    return this->target;
}
