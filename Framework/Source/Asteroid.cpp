#include "Asteroid.h"
#include <iostream>
using namespace std;

#include <glm/ext.hpp>
#include <GL/glew.h>

Asteroid::Asteroid() : SphereModel() {
    
}

Asteroid::Asteroid(vec3 position) : SphereModel(), lifeTime(0.0f) {
    // @TODO: update model mPosition based on transformations so it can be retrieved via mPosition easily
    this->mPosition = position; //+= vec3(model->GetWorldMatrix()[3]);
    this->mVelocity = vec3(2.0f, 2.0f, 2.0f); // temporary solution to give ellipse shape pointed towards the direction that it is shooting
    this->lifeTime = 50;
}

Asteroid::~Asteroid() {
}

void Asteroid::Update(float deltaTime) {
    //position
    vec3 worldOrigin = vec3(0.0f, 0.0f, 0.0f);
    vec3 currentPosition = this->GetPosition();
    vec3 difference = currentPosition - worldOrigin;
    
    this->mPosition = currentPosition - difference * deltaTime;
    //    vec2 finalPosition = bSpline(deltaTime);
    
    //    difference = currentPosition - vec3(finalPosition, 1);
    
}

void Asteroid::Draw(){
    SphereModel::Draw();
}

void Asteroid::setVelocity(vec3 velocity) {
    this->mVelocity = velocity;
}

ParticleSystem* Asteroid::getParticleSystem() {
    return this->mParticleSystem;
}

void Asteroid::setParticleSystem(ParticleSystem* ps) {
    this->mParticleSystem = ps;
}

//float smootherstep(float edge0, float edge1, float x)
//{
//    // Scale, and clamp x to 0..1 range
//    x = clamp((x - edge0)/(edge1 - edge0), 0.0, 1.0);
//    // Evaluate polynomial
//    return x*x*x*(x*(x*6 - 15) + 10);
//}

vec2 Asteroid::bSpline(float t) {
    
    float x = 3*pow(t, 2) - 6*pow(t, 3);
    float z = 3*pow(t, 2) - 6*pow(t, 3);
    
    cout << "x: " << x << ",z: " << z << endl;
    
    return vec2(x, z);
}
